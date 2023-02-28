#include <QMenu>
#include <QTabBar>
#include <QItemSelectionModel>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "filelistmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWindow->tabBar()->hide();
    model = new FileListModel(this);
    ui->listView->setModel(model);
    selection = new QItemSelectionModel(model);
    ui->listView->setSelectionModel(selection);
    ui->pbDeletePath->setDisabled(true);
    ui->textEdit->setReadOnly(true);

}

Ui::MainWindow* MainWindow::getUI() {
    return ui;
}

MainWindow::~MainWindow()
{
    delete ui;
}

