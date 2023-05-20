#include "mainwindow.h"
#include <QScreen>
#include <QMainWindow>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Get screen size
    /*QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();*/

    MainWindow w;
    //w.setGeometry(0, 0, screenWidth, screenHeight);
    w.show();

    return a.exec();
}
