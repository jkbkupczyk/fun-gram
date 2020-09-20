#include "filterwindow.h"
#include "ui_filterwindow.h"

#include <QtWidgets>

#include <QDesktopServices>
#include <QMessageBox>
#include <QMatrix3x3>
#include <cmath>

QImage filteredImg;
QLabel* label;

FilterWindow::FilterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FilterWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Fun-Gram(Filters)");

    QIcon icon(":/icons/img/16.png");
    this->setWindowIcon(icon);
    this->setMinimumSize(1600, 900);

}

FilterWindow::~FilterWindow()
{
    delete ui;
}

void FilterWindow::on_action_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());

    if(!fileName.isEmpty())
    {
        QImage img(fileName);
        ui->label->setPixmap(QPixmap::fromImage(img));
    }

}

void FilterWindow::on_action_Save_file_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"), QDir::currentPath(), tr("JPG (*.jpg);;PNG (*.png);;All file types (*.*)"));

    if(!fileName.isEmpty())
    {
        filteredImg.save(fileName);
    }

}

void FilterWindow::on_action_Quit_triggered()
{

    QMessageBox closeMsg;
    closeMsg.setWindowTitle(tr("Exit"));
    QIcon icon(":/icons/img/exit.png");

    closeMsg.setWindowIcon(icon);
    closeMsg.setText(tr("Are you really want to exit?"));

    QAbstractButton* bttnY = closeMsg.addButton(tr("Yes"), QMessageBox::YesRole);
    closeMsg.addButton(tr("No"), QMessageBox::NoRole);

    closeMsg.exec();

    if (closeMsg.clickedButton() == bttnY)
    {
        QApplication::quit();
    }

}


void FilterWindow::on_action_Gauss_Blur_triggered()
{

    QImage img = ui->label->pixmap()->toImage();

    QMatrix3x3 gaussKernel;
    gaussKernel(0, 0) = 1;  gaussKernel(0, 1) = 2;  gaussKernel(0, 2) = 1;
    gaussKernel(1, 0) = 2;  gaussKernel(1, 1) = 4;  gaussKernel(1, 2) = 2;
    gaussKernel(2, 0) = 1;  gaussKernel(2, 1) = 2;  gaussKernel(2, 2) = 1;

    float sum = 16.0;

    for(int i = 0 ; i<img.width()-1; i++)
    {
        for(int j = 0 ; j<img.height()-1; j++)
        {
            float red = 0, green = 0, blue = 0;

            red =
                    gaussKernel(0, 0) * qRed(img.pixel(i+1, j+1)) + gaussKernel(0, 1) * qRed(img.pixel(i, j+1)) + gaussKernel(0, 2) * qRed(img.pixel(i-1, j+1)) +
                    gaussKernel(1, 0) * qRed(img.pixel(i+1, j)) + gaussKernel(1, 1) * qRed(img.pixel(i, j)) + gaussKernel(1, 2) * qRed(img.pixel(i-1, j)) +
                    gaussKernel(2, 0) * qRed(img.pixel(i+1, j-1)) + gaussKernel(2, 1) * qRed(img.pixel(i, j-1)) + gaussKernel(2, 2) * qRed(img.pixel(i-1, j-1));

            green =
                    gaussKernel(0, 0) * qGreen(img.pixel(i+1, j+1)) + gaussKernel(0, 1) * qGreen(img.pixel(i, j+1)) + gaussKernel(0, 2) * qGreen(img.pixel(i-1, j+1)) +
                    gaussKernel(1, 0) * qGreen(img.pixel(i+1, j)) + gaussKernel(1, 1) * qGreen(img.pixel(i, j)) + gaussKernel(1, 2) * qGreen(img.pixel(i-1, j)) +
                    gaussKernel(2, 0) * qGreen(img.pixel(i+1, j-1)) + gaussKernel(2, 1) * qGreen(img.pixel(i, j-1)) + gaussKernel(2, 2) * qGreen(img.pixel(i-1, j-1));

            blue =
                    gaussKernel(0, 0) * qBlue(img.pixel(i+1, j+1)) + gaussKernel(0, 1) * qBlue(img.pixel(i, j+1)) + gaussKernel(0, 2) * qBlue(img.pixel(i-1, j+1)) +
                    gaussKernel(1, 0) * qBlue(img.pixel(i+1, j)) + gaussKernel(1, 1) * qBlue(img.pixel(i, j)) + gaussKernel(1, 2) * qBlue(img.pixel(i-1, j)) +
                    gaussKernel(2, 0) * qBlue(img.pixel(i+1, j-1)) + gaussKernel(2, 1) * qBlue(img.pixel(i, j-1)) + gaussKernel(2, 2) * qBlue(img.pixel(i-1, j-1));

            img.setPixel(i, j, qRgb(red/sum, green/sum, blue/sum));
        }
    }

    ui->label->setPixmap(QPixmap::fromImage(img));

}

void FilterWindow::on_action_Laplacian_Edge_Detection_triggered()
{

    QImage img = ui->label->pixmap()->toImage();

    QMatrix3x3 lapKernel;
    lapKernel(0, 0) = -1;    lapKernel(0, 1) = -1;    lapKernel(0, 2) = -1;
    lapKernel(1, 0) = -1;    lapKernel(1, 1) = 8;    lapKernel(1, 2) = -1;
    lapKernel(2, 0) = -1;    lapKernel(2, 1) = -1;    lapKernel(2, 2) = -1;


    for(int i = 0 ; i<img.width()-1; i++)
    {
        for(int j = 0 ; j<img.height()-1; j++)
        {
            float red = 0, green = 0, blue = 0;

            red =
                    lapKernel(0, 0) * qRed(img.pixel(i+1, j+1)) + lapKernel(0, 1) * qRed(img.pixel(i, j+1)) + lapKernel(0, 2) * qRed(img.pixel(i-1, j+1)) +
                    lapKernel(1, 0) * qRed(img.pixel(i+1, j)) + lapKernel(1, 1) * qRed(img.pixel(i, j)) + lapKernel(1, 2) * qRed(img.pixel(i-1, j)) +
                    lapKernel(2, 0) * qRed(img.pixel(i+1, j-1)) + lapKernel(2, 1) * qRed(img.pixel(i, j-1)) + lapKernel(2, 2) * qRed(img.pixel(i-1, j-1));

            green =
                    lapKernel(0, 0) * qGreen(img.pixel(i+1, j+1)) + lapKernel(0, 1) * qGreen(img.pixel(i, j+1)) + lapKernel(0, 2) * qGreen(img.pixel(i-1, j+1)) +
                    lapKernel(1, 0) * qGreen(img.pixel(i+1, j)) + lapKernel(1, 1) * qGreen(img.pixel(i, j)) + lapKernel(1, 2) * qGreen(img.pixel(i-1, j)) +
                    lapKernel(2, 0) * qGreen(img.pixel(i+1, j-1)) + lapKernel(2, 1) * qGreen(img.pixel(i, j-1)) + lapKernel(2, 2) * qGreen(img.pixel(i-1, j-1));

            blue =
                    lapKernel(0, 0) * qBlue(img.pixel(i+1, j+1)) + lapKernel(0, 1) * qBlue(img.pixel(i, j+1)) + lapKernel(0, 2) * qBlue(img.pixel(i-1, j+1)) +
                    lapKernel(1, 0) * qBlue(img.pixel(i+1, j)) + lapKernel(1, 1) * qBlue(img.pixel(i, j)) + lapKernel(1, 2) * qBlue(img.pixel(i-1, j)) +
                    lapKernel(2, 0) * qBlue(img.pixel(i+1, j-1)) + lapKernel(2, 1) * qBlue(img.pixel(i, j-1)) + lapKernel(2, 2) * qBlue(img.pixel(i-1, j-1));

            img.setPixel(i, j, qRgb(abs(red), abs(green), abs(blue)));
        }
    }

    ui->label->setPixmap(QPixmap::fromImage(img));

}

void FilterWindow::on_action_Gradient_Directional_Filter_triggered()
{

    QImage img = ui->label->pixmap()->toImage();

    QMatrix3x3 gradientKernel;
    gradientKernel(0, 0) = -1;    gradientKernel(0, 1) = 1;    gradientKernel(0, 2) = 1;
    gradientKernel(1, 0) = -1;    gradientKernel(1, 1) = -2;    gradientKernel(1, 2) = 1;
    gradientKernel(2, 0) = -1;    gradientKernel(2, 1) = 1;    gradientKernel(2, 2) = 1;

    for(int i = 0 ; i<img.width()-1; i++)
    {
        for(int j = 0 ; j<img.height()-1; j++)
        {
            float red = 0, green = 0, blue = 0;

            red =
                    gradientKernel(0, 0) * qRed(img.pixel(i+1, j+1)) + gradientKernel(0, 1) * qRed(img.pixel(i, j+1)) + gradientKernel(0, 2) * qRed(img.pixel(i-1, j+1)) +
                    gradientKernel(1, 0) * qRed(img.pixel(i+1, j)) + gradientKernel(1, 1) * qRed(img.pixel(i, j)) + gradientKernel(1, 2) * qRed(img.pixel(i-1, j)) +
                    gradientKernel(2, 0) * qRed(img.pixel(i+1, j-1)) + gradientKernel(2, 1) * qRed(img.pixel(i, j-1)) + gradientKernel(2, 2) * qRed(img.pixel(i-1, j-1));

            green =
                    gradientKernel(0, 0) * qGreen(img.pixel(i+1, j+1)) + gradientKernel(0, 1) * qGreen(img.pixel(i, j+1)) + gradientKernel(0, 2) * qGreen(img.pixel(i-1, j+1)) +
                    gradientKernel(1, 0) * qGreen(img.pixel(i+1, j)) + gradientKernel(1, 1) * qGreen(img.pixel(i, j)) + gradientKernel(1, 2) * qGreen(img.pixel(i-1, j)) +
                    gradientKernel(2, 0) * qGreen(img.pixel(i+1, j-1)) + gradientKernel(2, 1) * qGreen(img.pixel(i, j-1)) + gradientKernel(2, 2) * qGreen(img.pixel(i-1, j-1));

            blue =
                    gradientKernel(0, 0) * qBlue(img.pixel(i+1, j+1)) + gradientKernel(0, 1) * qBlue(img.pixel(i, j+1)) + gradientKernel(0, 2) * qBlue(img.pixel(i-1, j+1)) +
                    gradientKernel(1, 0) * qBlue(img.pixel(i+1, j)) + gradientKernel(1, 1) * qBlue(img.pixel(i, j)) + gradientKernel(1, 2) * qBlue(img.pixel(i-1, j)) +
                    gradientKernel(2, 0) * qBlue(img.pixel(i+1, j-1)) + gradientKernel(2, 1) * qBlue(img.pixel(i, j-1)) + gradientKernel(2, 2) * qBlue(img.pixel(i-1, j-1));

            img.setPixel(i, j, qRgb(abs(red), abs(green), abs(blue)));
        }
    }

    ui->label->setPixmap(QPixmap::fromImage(img));
}

void FilterWindow::on_action_Outline_Filter_triggered()
{

    QImage img = ui->label->pixmap()->toImage();

    QMatrix3x3 outlineKernel;
    outlineKernel(0, 0) = 1;    outlineKernel(0, 1) = 2;    outlineKernel(0, 2) = 1;
    outlineKernel(1, 0) = 0;    outlineKernel(1, 1) = 0;    outlineKernel(1, 2) = 0;
    outlineKernel(2, 0) = -1;    outlineKernel(2, 1) = -2;    outlineKernel(2, 2) = -1;

    for(int i = 0 ; i<img.width()-1; i++)
    {
        for(int j = 0 ; j<img.height()-1; j++)
        {
            float red = 0, green = 0, blue = 0;

            red =
                    outlineKernel(0, 0) * qRed(img.pixel(i+1, j+1)) + outlineKernel(0, 1) * qRed(img.pixel(i, j+1)) + outlineKernel(0, 2) * qRed(img.pixel(i-1, j+1)) +
                    outlineKernel(1, 0) * qRed(img.pixel(i+1, j)) + outlineKernel(1, 1) * qRed(img.pixel(i, j)) + outlineKernel(1, 2) * qRed(img.pixel(i-1, j)) +
                    outlineKernel(2, 0) * qRed(img.pixel(i+1, j-1)) + outlineKernel(2, 1) * qRed(img.pixel(i, j-1)) + outlineKernel(2, 2) * qRed(img.pixel(i-1, j-1));

            green =
                    outlineKernel(0, 0) * qGreen(img.pixel(i+1, j+1)) + outlineKernel(0, 1) * qGreen(img.pixel(i, j+1)) + outlineKernel(0, 2) * qGreen(img.pixel(i-1, j+1)) +
                    outlineKernel(1, 0) * qGreen(img.pixel(i+1, j)) + outlineKernel(1, 1) * qGreen(img.pixel(i, j)) + outlineKernel(1, 2) * qGreen(img.pixel(i-1, j)) +
                    outlineKernel(2, 0) * qGreen(img.pixel(i+1, j-1)) + outlineKernel(2, 1) * qGreen(img.pixel(i, j-1)) + outlineKernel(2, 2) * qGreen(img.pixel(i-1, j-1));

            blue =
                    outlineKernel(0, 0) * qBlue(img.pixel(i+1, j+1)) + outlineKernel(0, 1) * qBlue(img.pixel(i, j+1)) + outlineKernel(0, 2) * qBlue(img.pixel(i-1, j+1)) +
                    outlineKernel(1, 0) * qBlue(img.pixel(i+1, j)) + outlineKernel(1, 1) * qBlue(img.pixel(i, j)) + outlineKernel(1, 2) * qBlue(img.pixel(i-1, j)) +
                    outlineKernel(2, 0) * qBlue(img.pixel(i+1, j-1)) + outlineKernel(2, 1) * qBlue(img.pixel(i, j-1)) + outlineKernel(2, 2) * qBlue(img.pixel(i-1, j-1));

            img.setPixel(i, j, qRgb(abs(red), abs(green), abs(blue)));
        }
    }

    ui->label->setPixmap(QPixmap::fromImage(img));
}

void FilterWindow::on_action_Help_triggered()
{
    QMessageBox helpMsg;
    helpMsg.setWindowTitle("Help");
    QIcon icon(":/icons/img/info.png");

    helpMsg.setWindowIcon(icon);
    helpMsg.setText(tr("If you want to filter image, firstly you have to load that image simply by pressing \"Open\" in menu bar then search for \"Filter\""
                       "and choose filter you want to use!"));

    QAbstractButton* bttn;
    bttn = helpMsg.addButton(tr("Got it!"), QMessageBox::YesRole);

    helpMsg.exec();
}

void FilterWindow::on_action_About_filters_triggered()
{
    QMessageBox redirectMsg;
    redirectMsg.setWindowTitle(tr("About filtering"));
    QIcon icon(":/icons/img/web.png");

    redirectMsg.setWindowIcon(icon);
    redirectMsg.setText(tr("You are about to be redirected to an external page!\nContinue?"));

    QAbstractButton* bttn;
    bttn = redirectMsg.addButton(tr("Yes"), QMessageBox::YesRole);
    redirectMsg.addButton(tr("No"), QMessageBox::NoRole);

    redirectMsg.exec();

    if (redirectMsg.clickedButton() == bttn)
    {
        QDesktopServices::openUrl(QUrl("https://en.wikipedia.org/wiki/Kernel_(image_processing)"));
    }
}
