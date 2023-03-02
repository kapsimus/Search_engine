#include <QAction>
#include <QMenu>
#include <QStringListModel>
#include <QStringList>
#include <QListView>
#include <QFileDialog>
#include <QFile>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "InvertedIndex.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    Ui::MainWindow &window = *w.getUI();
    QStringList fileList;
    ConverterJSON &conv = w.settings->converter();
    InvertedIndex &index = w.settings->index();
    SearchServer &server = w.settings->server();

    //добавить файлы из меню
    QObject::connect(window.action_AddFiles, &QAction::triggered, &a,[&fileList, &w](){
        fileList = QFileDialog::getOpenFileNames(&w,"", QDir::current().absolutePath(), "*.txt", nullptr);
        for (QString &path: fileList) {
        w.model->addValue(path);
        }
    });
    //добавить файлы кнопкой
    QObject::connect(window.pbAddFiles, &QPushButton::clicked, &a, [&fileList, &w](){
        fileList = QFileDialog::getOpenFileNames(&w,"", QDir::current().absolutePath(), "*.txt", nullptr);
        for (QString &path: fileList) {
        w.model->addValue(path);
        }
    });
    //удалить файлы
    QObject::connect(window.pbDeletePath, &QPushButton::clicked, &a, [&w](){
        w.model->deleteValues(w.selection->selection());
    });
    //отключение-включение кнопки Delete при выделении, вывод текста файла при единичном выделении
    QObject::connect(w.selection, &QItemSelectionModel::selectionChanged, &a, [&w, &window](){
        if (w.selection->hasSelection()) {
            window.pbDeletePath->setDisabled(false);
        } else {
            window.pbDeletePath->setDisabled(true);
        }
        QString text;
        QFile file(w.model->selectedRowData(w.selection->selection()).toString());
        if (file.exists()) {
            if (file.open(QIODevice::ReadOnly)) {
                 QTextStream stream(&file);
                 text = stream.readAll();
                 file.close();
            }
        }
        window.textEdit->setText(text);
    });
    QObject::connect(window.pbCancelPaths, &QPushButton::clicked, &a, [&window](){
        window.tabWindow->setCurrentIndex(0);
    });
    QObject::connect(window.pbCancelSettings, &QPushButton::clicked, &a, [&window](){
        window.tabWindow->setCurrentIndex(0);
    });

    //действия из меню
    QObject::connect(window.action_Exit, &QAction::triggered, &a, [&a](){
        a.quit();
    });
    QObject::connect(window.action_Requests, &QAction::triggered, [&window](){
        window.tabWindow->setCurrentIndex(1);
    });
    QObject::connect(window.action_Ansvers, &QAction::triggered, [&window](){
        window.tabWindow->setCurrentIndex(2);
    });
    QObject::connect(window.action_Paths, &QAction::triggered, [&window](){
        window.tabWindow->setCurrentIndex(3);
    });
    QObject::connect(window.action_Config, &QAction::triggered, [&window](){
        window.tabWindow->setCurrentIndex(4);
    });
    QObject::connect(window.action_Help, &QAction::triggered, [&window](){
        window.tabWindow->setCurrentIndex(5);
    });
    QObject::connect(window.action_About, &QAction::triggered, [&window](){
        window.tabWindow->setCurrentIndex(6);
    });
    QObject::connect(window.action_RemoveFiles, &QAction::triggered, [&window](){
        window.tabWindow->setCurrentIndex(0);
    });
    w.show();
    return a.exec();
}
