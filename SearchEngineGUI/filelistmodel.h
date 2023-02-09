#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QAbstractTableModel>
#include <QObject>

class FileListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FileListModel(int rows, int cols, QObject *parent = nullptr);
private:
    int _rowCount = 0;
    int _colCount = 0;
protected:
    QHash<QModelIndex, QVariant> _rowData;

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
};

class SimpleFileListModel: public FileListModel
{
    Q_OBJECT
public:
    SimpleFileListModel(int rows, QObject *parent = nullptr);
    void setFilePath(int rowNum, QString path);

    // QAbstractItemModel interface
public:
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // FILELISTMODEL_H
