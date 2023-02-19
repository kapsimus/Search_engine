#include "filelistmodel.h"
#include <algorithm>


FileListModel::FileListModel(QObject *parent): QAbstractItemModel(parent)
{

}

QModelIndex FileListModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column, (void*)&_data[row]);
}

QModelIndex FileListModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int FileListModel::rowCount(const QModelIndex &parent) const
{
    return _data.size();
}

int FileListModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant FileListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return _data.at(index.row());
    }
    return QVariant();
}

bool FileListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (_data.isEmpty() || _data.size() <= row) {
        return false;
    } else {
    _data.removeAt(row);
    emit layoutChanged();
    return true;
    }
}

void FileListModel::addValue(const QString &value)
{
    _data.append(value);
    emit layoutChanged();
}

void FileListModel::deleteValues(const QItemSelection &selected)
{
    QModelIndexList items = selected.indexes();
    std::sort(items.begin(), items.end());
    int countRow = items.count();
    for( int i = countRow; i > 0; i--) {
        beginRemoveRows(QModelIndex(), 0, items.at(i-1).row());
        removeRows( items.at(i-1).row(), 1, QModelIndex());
        endRemoveRows();
    }
}
