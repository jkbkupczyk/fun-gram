#include "mainwindow.h"
#include <QApplication>
#include <QWidget>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow paintWindow;
    paintWindow.show();

    return app.exec();
}
