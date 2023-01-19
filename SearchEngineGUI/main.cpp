#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QMenuBar menuBar(&w);
    QMenu menu("&File");
    menu.addAction("&Add files", &w, SLOT(AddFiles()));
    menu.addSeparator();
    menu.addAction("&Exit", &a, SLOT(quit()));
    menuBar.addMenu(&menu);
    menuBar.show();
    w.show();
    return a.exec();
}
