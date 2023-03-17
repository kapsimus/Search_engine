#include <QMenu>
#include <QTabBar>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QAction>
#include <QMenu>
#include <QStringListModel>
#include <QStringList>
#include <QListView>
#include <QFileDialog>
#include <QFile>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "filelistmodel.h"
#include "InvertedIndex.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    settings = new Settings();
    settings->loadSettings();
    QStringList fileList;
    ConverterJSON &conv = settings->converter();
    InvertedIndex &index = settings->index();
    SearchServer &server = settings->server();

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
    ui->leRequestsPath->setText(settings->requestPath());
    ui->leFilesPath->setText(settings->filesFolderPath());

    model = new FileListModel(this);
    ui->listView->setModel(model);
    selection = new QItemSelectionModel(model);
    ui->listView->setSelectionModel(selection);

    requestModel = new FileListModel(this);
    ui->lvRequest->setEditTriggers(QAbstractItemView::AllEditTriggers);
    requestDelegate = new LineEditDelegate(ui->lvRequest);
    ui->lvRequest->setItemDelegate(requestDelegate);
    ui->lvRequest->setModel(requestModel);
    requestSelection = new QItemSelectionModel(requestModel);
    ui->lvRequest->setSelectionModel(requestSelection);


    //добавить файлы из меню
    QObject::connect(ui->action_AddFiles, &QAction::triggered, [&fileList, this](){
        fileList = QFileDialog::getOpenFileNames(this,"", QDir::current().absolutePath(), "*.txt", nullptr);
        for (QString &path: fileList) {
        model->addValue(path);
        }
    });
    //добавить файлы кнопкой
    QObject::connect(ui->pbAddFiles, &QPushButton::clicked, [&fileList, this](){
        fileList = QFileDialog::getOpenFileNames(this,"", QDir::current().absolutePath(), "*.txt", nullptr);
        for (QString &path: fileList) {
        model->addValue(path);
        }
    });
    //удалить файлы
    QObject::connect(ui->pbDeletePath, &QPushButton::clicked, [this](){
        model->deleteValues(selection->selection());
    });
    //отключение-включение кнопки Delete при выделении, вывод текста файла при единичном выделении
    QObject::connect(selection, &QItemSelectionModel::selectionChanged, [this](){
        if (selection->hasSelection()) {
            ui->pbDeletePath->setDisabled(false);
        } else {
            ui->pbDeletePath->setDisabled(true);
        }
        QString text;
        QFile file(model->selectedRowData(selection->selection()).toString());
        if (file.exists()) {
            if (file.open(QIODevice::ReadOnly)) {
                 QTextStream stream(&file);
                 text = stream.readAll();
                 file.close();
            }
        }
        ui->textEdit->setText(text);
    });
    // кнопка Cancel в меню Paths
    QObject::connect(ui->pbCancelPaths, &QPushButton::clicked, [this](){
        ui->tabWindow->setCurrentIndex(0);
    });
    // кнопка Cancel в меню Settings
    QObject::connect(ui->pbCancelSettings, &QPushButton::clicked, [this](){
        ui->tabWindow->setCurrentIndex(0);
    });
    // нормализация текста (кнопка Normalise)
    QObject::connect(ui->pbNormalize, &QPushButton::clicked, [this](){
        QFile file(model->selectedRowData(selection->selection()).toString());
        if (file.exists()) {
            if (file.open(QIODevice::ReadWrite)) {
                 QTextStream stream(&file);
                 QString text = stream.readAll();
                 std::string str = text.toStdString();
                 str = settings->converter().NormalizeDocument(str);
                 text = QString::fromStdString(str);
                 file.resize(0);
                 file.write(text.toStdString().c_str());
                 file.close();
            }
        }

    });
    QObject::connect(ui->pbAddRequest, &QPushButton::clicked, [this](){
        requestModel->addValue(ui->leRequest->text());
        ui->leRequest->clear();
    });

    //действия из меню
    QObject::connect(ui->action_Exit, &QAction::triggered, [this](){
        this->close();
    });
    QObject::connect(ui->action_Requests, &QAction::triggered, [this](){
        ui->tabWindow->setCurrentIndex(1);
    });
    QObject::connect(ui->action_Ansvers, &QAction::triggered, [this](){
       ui->tabWindow->setCurrentIndex(2);
    });
    QObject::connect(ui->action_Paths, &QAction::triggered, [this](){
        ui->tabWindow->setCurrentIndex(3);
    });
    QObject::connect(ui->action_Config, &QAction::triggered, [this](){
        ui->tabWindow->setCurrentIndex(4);
    });
    QObject::connect(ui->action_Help, &QAction::triggered, [this](){
        ui->tabWindow->setCurrentIndex(5);
    });
    QObject::connect(ui->action_About, &QAction::triggered, [this](){
        ui->tabWindow->setCurrentIndex(6);
    });
    QObject::connect(ui->action_RemoveFiles, &QAction::triggered, [this](){
        ui->tabWindow->setCurrentIndex(0);
    });

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

