#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSize windowSize(800, 600);
    w.setMinimumSize(windowSize);
    QWidget window(&w);
    window.setMinimumSize(w.size());
    QMenuBar menuBar(&w);
    QMenu menu("&File");
    menu.addAction("&Add files", &w, SLOT(AddFiles()));
    menu.addSeparator();
    menu.addAction("&Exit", &a, SLOT(quit()));
    QMenu pref("&Preferences");
    pref.addAction("&Files Paths", &w, SLOT(SetPaths()));
    pref.addSeparator();
    pref.addAction("&Config", &w, SLOT(SetConfig()));
    menuBar.addMenu(&menu);
    menuBar.addMenu(&pref);
    QHBoxLayout menuLayout(&window);
    menuLayout.addWidget(&menuBar);
    menuBar.show();
    w.show();
    window.show();
    return a.exec();
}
