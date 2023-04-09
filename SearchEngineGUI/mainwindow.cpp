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
#include <QRegularExpression>
#include <QMessageBox>
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
    ui->lvFiles->setModel(model);
    ui->lvFiles->setEditTriggers(QAbstractItemView::NoEditTriggers);
    selection = new QItemSelectionModel(model);
    ui->lvFiles->setSelectionModel(selection);

    requestModel = new FileListModel(this);
    ui->lvRequest->setModel(requestModel);
    ui->lvRequest->setEditTriggers(QAbstractItemView::NoEditTriggers);
    requestSelection = new QItemSelectionModel(requestModel);
    ui->lvRequest->setSelectionModel(requestSelection);


    //добавить файлы из меню
    QObject::connect(ui->action_AddFiles, &QAction::triggered, this, &MainWindow::addFiles);

    //добавить файлы кнопкой
    QObject::connect(ui->pbAddFiles, &QPushButton::clicked, this, &MainWindow::addFiles);

    //удалить файлы
    QObject::connect(ui->pbDeletePath, &QPushButton::clicked, this, [this](){
        model->deleteValues(selection->selection());
    });
    //удалить запросы (delete request)
    QObject::connect(ui->pbDeleteRequest, &QPushButton::clicked, this, [this](){
        requestModel->deleteValues(requestSelection->selection());
    });
    //сохранить запросы в файл requests.json (Save Requests)
    QObject::connect(ui->pbSaveRequests, &QPushButton::clicked, this, [this, &conv](){
        std::vector<std::string> listRequest;
        for (int i = 0; i < requestModel->rowCount(QModelIndex()); ++i) {
            QModelIndex index = requestModel->index(i, 0, QModelIndex());
            QVariant request = requestModel->data(index, Qt::DisplayRole);
            listRequest.push_back(request.toString().toStdString());
        }
        if (conv.SetRequests(listRequest)) {
            QMessageBox::information(this, "Sucess", "Request saved");
        } else {
            QMessageBox::information(this, "Error", "Request not saved");
        }
    });


    //отключение-включение кнопки Delete при выделении, вывод текста файла при единичном выделении
    QObject::connect(selection, &QItemSelectionModel::selectionChanged, this, [this](){
        if (selection->hasSelection()) {
            ui->pbDeletePath->setDisabled(false);
        } else {
            ui->pbDeletePath->setDisabled(true);
            return;
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
    QObject::connect(ui->pbCancelPaths, &QPushButton::clicked, this, [this](){
        ui->tabWindow->setCurrentIndex(0);
    });
    // кнопка Cancel в меню Settings
    QObject::connect(ui->pbCancelSettings, &QPushButton::clicked, this, [this](){
        ui->tabWindow->setCurrentIndex(0);
    });
    // нормализация текста (кнопка Normalise)
    QObject::connect(ui->pbNormalize, &QPushButton::clicked, this, [this](){
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

    //кнопка добавления запроса Add Request
    QObject::connect(ui->pbAddRequest, &QPushButton::clicked, this, &MainWindow::addRequest);

    //добавление запроса нажатием клавиши Enter
    QObject::connect(ui->leRequest, &QLineEdit::returnPressed, this, &MainWindow::addRequest);


    //действия из меню
    QObject::connect(ui->action_Exit, &QAction::triggered, this, [this](){
        this->close();
    });
    QObject::connect(ui->action_Requests, &QAction::triggered, this, [this](){
        ui->tabWindow->setCurrentIndex(1);
        ui->leRequest->setFocus();
    });
    QObject::connect(ui->action_Ansvers, &QAction::triggered, this, [this](){
       ui->tabWindow->setCurrentIndex(2);
    });
    QObject::connect(ui->action_Paths, &QAction::triggered, this, [this](){
        ui->tabWindow->setCurrentIndex(3);
    });
    QObject::connect(ui->action_Config, &QAction::triggered, this, [this](){
        ui->tabWindow->setCurrentIndex(4);
    });
    QObject::connect(ui->action_Help, &QAction::triggered, this, [this](){
        ui->tabWindow->setCurrentIndex(5);
    });
    QObject::connect(ui->action_About, &QAction::triggered, this, [this](){
        ui->tabWindow->setCurrentIndex(6);
    });
    QObject::connect(ui->action_RemoveFiles, &QAction::triggered, this, [this](){
        ui->tabWindow->setCurrentIndex(0);
    });

}

Ui::MainWindow* MainWindow::getUI() {
    return ui;
}

MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}

void MainWindow::addRequest()
{
    QStringList list = ui->leRequest->text().split(QRegularExpression("\\s+"));
    for (const auto &word: list) {
        if (!QRegularExpression("(^[a-z]+$)|(^[0-9]+$)|(^[a-z]+-[a-z]+$)").match(word).hasMatch()) {
            QMessageBox::information(this, "Error", "Wrong request!");
            ui->leRequest->setFocus();
            return;
        }
    }
    requestModel->addValue(ui->leRequest->text());
    ui->leRequest->clear();
    ui->leRequest->setFocus();
}

void MainWindow::addFiles()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this,"", QDir::current().absolutePath(), "*.txt", nullptr);
    for (QString &path: fileList) {
        model->addValue(path);
    }
}

