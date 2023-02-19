#include <QAction>
#include <QMenu>
#include <QStringListModel>
#include <QStringList>
#include <QListView>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    Ui::MainWindow &window = *w.getUI();
    QStringList fileList{"kjhkjh", "jhgfhgf"};

    QObject::connect(window.action_AddFiles, &QAction::triggered, [&fileList, &w](){
        fileList = QFileDialog::getOpenFileNames(&w,"", "d:/", "*.txt", nullptr);
        for (QString &path: fileList) {
        w.model->addValue(path);
        }
    });
    QObject::connect(window.pbDeletePath, &QPushButton::clicked, [&w](){
        w.model->deleteValues(w.selection->selection());
    });


    QObject::connect(window.action_Exit, &QAction::triggered, [&a](){
        a.quit();
    });
    QObject::connect(window.action_Paths, &QAction::triggered, [&window](){
        window.tabWindow->setCurrentIndex(1);
    });
    QObject::connect(window.action_Config, &QAction::triggered, [&window](){
        window.tabWindow->setCurrentIndex(2);
    });
    QObject::connect(window.action_Help, &QAction::triggered, [&window](){
        window.tabWindow->setCurrentIndex(3);
    });
    QObject::connect(window.action_About, &QAction::triggered, [&window](){
        window.tabWindow->setCurrentIndex(4);
    });
    QObject::connect(window.action_RemoveFiles, &QAction::triggered, [&window](){
        window.tabWindow->setCurrentIndex(0);
    });
    w.show();
    return a.exec();
}
