#include <QMenu>
#include <QTabBar>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "filelistmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWindow->tabBar()->hide();

    SimpleFileListModel model(10, this);
    model.setFilePath(0, "12345");
    model.setFilePath(1, "1111111");
    model.setFilePath(4, "44444");
    ui->tableView->setModel(model);
}

Ui::MainWindow* MainWindow::getUI() {
    return ui;
}

MainWindow::~MainWindow()
{
    delete ui;
}

