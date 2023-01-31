#include <QFileDialog>
#include <QMenu>
#include <QTabBar>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWindow->tabBar()->hide();
}

void MainWindow::AddFiles() {
    QString strFilter;
    QStringList strList = QFileDialog::getOpenFileNames(this,"", "d:/", "*.txt", nullptr);
}
Ui::MainWindow* MainWindow::getUI() {
    return ui;
}

MainWindow::~MainWindow()
{
    delete ui;
}

