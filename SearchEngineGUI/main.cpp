
#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    Ui::MainWindow &window = *w.getUI();

    w.show();
    return a.exec();
}
