#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include <QMainWindow>

namespace Ui {
class FilterWindow;
}

class FilterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FilterWindow(QWidget *parent = nullptr);
    ~FilterWindow();

private slots:

	/* Open file */
    void on_action_Open_triggered();

	/* Save file */
    void on_action_Save_file_triggered();

	/* Quit filter window */
    void on_action_Quit_triggered();

	/* Perform gauss blur on image */
    void on_action_Gauss_Blur_triggered();

	/* Perform laplacian edge detection on image */
    void on_action_Laplacian_Edge_Detection_triggered();

	/* Perform gradient directional filtering on image */
    void on_action_Gradient_Directional_Filter_triggered();

	/* Perform outline filtering on image */
    void on_action_Outline_Filter_triggered();

	/* Displays Help  */
    void on_action_Help_triggered();

	/* Redirect user to website */
    void on_action_About_filters_triggered();

private:
    Ui::FilterWindow *ui;
};

#endif // FILTERWINDOW_H
