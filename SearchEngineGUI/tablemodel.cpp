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
        return 4;
    }
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            return QString::fromLatin1(_data[index.row()].requestId);
        } else if (index.column() == 1) {
            return _data[index.row()].result;
        } else if (index.column() == 2) {
            return _data[index.row()].docId == -1 ? "Empty" : QString::number(_data[index.row()].docId);
        } else if (index.column() == 3) {
            return _data[index.row()].rank == -1 ? "Empty" : QString::number(_data[index.row()].rank, 'f', 12);
        }
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
        return QString::fromLatin1(_data[items.begin()->row()].requestId);
    }
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << role;
    return true;
}

void TableModel::addValue(const Answer &value)
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

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
             return QVariant();
    if (orientation == Qt::Horizontal) {
        if(section == 0) {
            return QString("Request ID");
        } else if(section == 1) {
            return QString{"Result"};
        } else if(section == 2) {
            return QString{"Document ID"};
        } else if(section == 3) {
            return QString{"Rank"};
        }
    } else {
        return QString("Row %1").arg(section);
    }
    return QVariant();
}
