#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

//Widget for drawing
class ScribbleArea;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    /* stops events from executing*/
    void closeEvent(QCloseEvent *event) override;

private slots:
    /* Exits program */
    void exit();

    /* open image file */
    void open();

    /* save image file */
    void save();

    /* changes pencil color */
    void penColor();

    /* changes pencil width */
    void penWidth();

    /* displays about dialog */
    void about();

    void openFilters();

private:
    /* creates actions */
    void createActs();

    /* creates menu system*/
    void createMenu();

    /* save if changes occur */
    bool maybeSave();

    /* save file */
    bool saveFile(const QByteArray &file);

    /* paint area where draw */
    ScribbleArea *scribbleArea;

    /* MENU BAR components */
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;
    QMenu *filterMenu;

    /* QList for all our Actions below */
    QList<QAction *> saveAsActs;

    QAction *exitAct;
    QAction *openAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *clsAct;
    QAction *aboutAct;

    /* Filter Action */
    QAction *openFilterAct;

    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
