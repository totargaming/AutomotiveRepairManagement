#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
//qmake: qmake.exe AutomotiveRepairManagement.pro
//Make: mingw32-make.exe -j12 in E:\Workspace\AutomotiveRepairManagement\DebugVersion
