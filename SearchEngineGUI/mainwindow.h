#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include <QStandardItemModel>
#include <QStringList>
#include "filelistmodel.h"
#include "settings.h"
#include "lineeditdelegate.h"
#include "tablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow* getUI();
    FileListModel *requestModel;
    FileListModel *model;
    TableModel *answersModel;
    QItemSelectionModel *selection;
    QItemSelectionModel *requestSelection;
    LineEditDelegate *requestDelegate;
    Settings *settings;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void addRequest();
    void addFiles();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
