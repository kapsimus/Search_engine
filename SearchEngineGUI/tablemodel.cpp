#include "tablemodel.h"
#include <algorithm>
#include <vector>
#include <string>


TableModel::TableModel(QObject *parent): QAbstractItemModel(parent)
{

}

QModelIndex TableModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column, (void*)&_data[row]);
}

QModelIndex TableModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return _data.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (_data.empty()) {
        return 0;
    } else {
        return _data[0].size();
    }
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return _data.at(index.row()).at(index.column());
    }
    return QVariant();
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (_data.isEmpty() || _data.size() <= row) {
        return false;
    } else {
    _data.removeAt(row);
    emit layoutChanged();
    return true;
    }
}

QVariant TableModel::selectedRowData(const QItemSelection &selected)
{
    QModelIndexList items = selected.indexes();
    if (items.size() != 1) {
        return QVariant();
    } else {
        return _data[items.begin()->row()][items.begin()->column()];
    }
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << role;
    return true;
}

void TableModel::addValue(const QStringList &value)
{
    _data.append(value);
    emit layoutChanged();
}

void TableModel::deleteValues(const QItemSelection &selected)
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

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
