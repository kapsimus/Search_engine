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
    settings = new Settings();
    settings->loadSettings();

    ui->setupUi(this);
    ui->lProgramName->setText(settings->name());
    ui->lVersion->setText(settings->version());
    ui->leMaxResponses->setText(QString::number(settings->maxResponses()));
    ui->tabWindow->tabBar()->hide();
    ui->tabWindow->setCurrentIndex(0);
    ui->pbDeletePath->setDisabled(true);
    ui->textEdit->setReadOnly(true);
    ui->leConfigPath->setText(settings->configPath());
    ui->leAnswersPath->setText(settings->answerPath());
    model = new FileListModel(this);
    ui->listView->setModel(model);
    selection = new QItemSelectionModel(model);
    ui->listView->setSelectionModel(selection);

}

Ui::MainWindow* MainWindow::getUI() {
    return ui;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete selection;
    delete settings;
}

