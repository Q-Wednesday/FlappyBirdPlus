#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Flappy Bird");
    w.setWindowIcon(QIcon(":/images/bird0"));
    w.show();
    return a.exec();
}
