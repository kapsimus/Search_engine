#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include "filelistmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow* getUI();
    FileListModel *model;
    QItemSelectionModel *selection;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
