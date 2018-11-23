#include "mainwindow.h"
#include "configdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *mw;
    mw = new MainWindow;

    mw->show();

    return a.exec();
}
