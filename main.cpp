#include "mainwindow.h"
#include <QApplication>
#include "controles.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    Controles c;
    c.show();

    return a.exec();
}
