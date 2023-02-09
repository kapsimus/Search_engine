#include "filelistmodel.h"

FileListModel::FileListModel(int rows, int cols, QObject *parent)
    :QAbstractTableModel(parent), _rowCount(rows), _colCount(cols)
{

}

int FileListModel::rowCount(const QModelIndex &parent) const
{
    return _rowCount;
}

int FileListModel::columnCount(const QModelIndex &parent) const
{
    return -_colCount;
}

QVariant FileListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    } else if (role == Qt::DisplayRole) {
        return _rowData.value(index, QVariant());
    }
    return QVariant();

}

bool FileListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    } else if (role == Qt::DisplayRole) {
        _rowData.insert(index, value);
        emit dataChanged(index, index);
    }
    return false;
}

Qt::ItemFlags FileListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

SimpleFileListModel::SimpleFileListModel(int rows, QObject *parent): FileListModel(rows, 1, parent)
{

}

void SimpleFileListModel::setFilePath(int rowNum, QString path)
{
    setData(index(rowNum - 1, 0), path, Qt::EditRole);
}

QVariant SimpleFileListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    } else if (orientation == Qt::Horizontal) {
        return "Path";
    } else {
        return QString("%3").arg(section + 1);
    }
}
