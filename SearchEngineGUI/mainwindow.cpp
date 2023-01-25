#include "mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

MainWindow::~MainWindow()
{
}
void MainWindow::AddFiles() {
    QString strFilter;
    QStringList strList = QFileDialog::getOpenFileNames(this,"", "d:/", "*.txt", nullptr);
}
void MainWindow::SetPaths() {

}
void MainWindow::SetConfig() {

}
