#include "mainwindow.h"

#include <QApplication>

#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Get the screen size
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    // Calculate the position of the main window
    int x = (screenGeometry.width() - w.width()) / 2 + 150;  // Center the window and shift it 100 pixels to the right
    int y = (screenGeometry.height() - w.height()) / 2;

    // Move the main window to the calculated position
    w.move(x, y);

    w.show();
    return a.exec();
}
