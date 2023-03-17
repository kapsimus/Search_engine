#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once
#include <QMainWindow>
#include <QStandardItemModel>
#include <QStringList>
#include "filelistmodel.h"
#include "settings.h"
#include "lineeditdelegate.h"

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
    QItemSelectionModel *selection;
    QItemSelectionModel *requestSelection;
    LineEditDelegate *requestDelegate;
    Settings *settings;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
