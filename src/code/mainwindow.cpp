#include "ui_mainwindow.h"
#include "scribblearea.h"
#include "mainwindow.h"
#include "filterwindow.h"

#include <QtWidgets>
#include <QMessageBox>
#include <QMatrix3x3>
#include <QImage>
#include <QLabel>
#include <QDesktopWidget>
#include <QStyle>

#include <QTextStream>

/* MainWindow Constructor */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    scribbleArea = new ScribbleArea;
    QIcon icon(":/icons/img/mainicon16x.png");

    setCentralWidget(scribbleArea);
    createActs();
    createMenu();
    setWindowTitle("Fun-Gram");
    setMinimumSize(1280, 720);
    setWindowIcon(icon);
}

/* MainWindow Destructor */
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave())
        event->accept();
    else
        event->ignore();
}

void MainWindow::open()
{
    if(maybeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
        if(!fileName.isEmpty())
            scribbleArea->openImg(fileName);
    }
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();

    saveFile(fileFormat);
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());

    if(newColor.isValid())
        scribbleArea->setPenColor(newColor);
}       

void MainWindow::penWidth()
{
    bool ok;

    int newWidth = QInputDialog::getInt(this, tr("Pen Width"), tr("Please select your pen width : "), scribbleArea->penWidth(), 1, 50, 1, &ok);

    if(ok)
        scribbleArea->setPenWidth(newWidth);
}

void MainWindow::about()
{
    QMessageBox aboutBox;
    aboutBox.setWindowTitle("About Fun-Gram");
    QIcon icon(":/icons/img/info");

    aboutBox.setWindowIcon(icon);
    aboutBox.setText(tr("Fun-Gram is a free paint type application, that let's you draw and edit raster graphics"));

    QAbstractButton* bttn;
    bttn = aboutBox.addButton(tr("Great!"), QMessageBox::YesRole);

    aboutBox.exec();
}

void MainWindow::createActs()
{
    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    foreach(QByteArray format, QImageWriter::supportedImageFormats())
    {
        QString text = tr("%1...").arg(QString(format).toUpper());
        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }

    printAct = new QAction(tr("&Print..."), this);
    connect(printAct, SIGNAL(triggered()), scribbleArea, SLOT(printImg()));

    exitAct = new QAction(tr("&Exit"), this);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(exit()));
    
    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAct = new QAction(tr("&Pen Width..."), this);
    penWidthAct->setShortcut(tr("Ctrl + Q"));
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));
    
    clsAct = new QAction(tr("&Cls"), this);
    clsAct->setShortcut(tr("Ctrl+C"));
    connect(clsAct, SIGNAL(triggered()), scribbleArea, SLOT(clearImg()));
    
    aboutAct = new QAction(tr("&About..."), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    openFilterAct = new QAction(tr("&Open filters"), this);
    connect(openFilterAct, SIGNAL(triggered()), this, SLOT(openFilters()));
}

void MainWindow::createMenu()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);

    foreach(QAction *action, saveAsActs)
    {
        saveAsMenu->addAction(action);
    }

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    filterMenu = new QMenu(tr("&Filters"),  this);
    filterMenu->addAction(openFilterAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clsAct);
    

    helpMenu = new QMenu(tr("&About"), this);
    //helpMenu->addAction(helpAct);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutAct);
    
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(filterMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);

}

bool MainWindow::maybeSave(){
    if(scribbleArea->isModified())
    {
        QMessageBox::StandardButton retVal;
        retVal = QMessageBox::warning(this, tr("Fun-Gram"),
                                   tr("This image has been modified.\nDo you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if(retVal == QMessageBox::Save)
            return saveFile("png");
        else if (retVal == QMessageBox::Cancel)
            return false;
    }

    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/*." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
        initialPath, tr("%1 Files (*,%2);; All Files(*)").arg(QString::fromLatin1(fileFormat.toUpper())).arg(QString::fromLatin1(fileFormat)));

    if (fileName.isEmpty())
    {
        return false;
    }
    else
    {
        return scribbleArea->saveImg(fileName, fileFormat.constData());
    }
}

void MainWindow::exit()
{
    QMessageBox closeMsg;
    closeMsg.setWindowTitle(tr("Exit"));
    QIcon exitI(":/icons/img/exit.png");

    closeMsg.setWindowIcon(exitI);
    closeMsg.setText(tr("Are you really want to exit?"));

    QAbstractButton* bttnY = closeMsg.addButton(tr("Yes"), QMessageBox::YesRole);
    closeMsg.addButton(tr("No"), QMessageBox::NoRole);

    closeMsg.exec();

    if (closeMsg.clickedButton() == bttnY)
    {
        QApplication::quit();
    }
}

void MainWindow::openFilters()
{
    FilterWindow *fWindow;
    fWindow = new FilterWindow;

    fWindow->show();
}
