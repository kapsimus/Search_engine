#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractItemModel>
#include <QItemSelection>
#include <QObject>
#include <QStringList>
#include "answer.h"

class TableModel : public QAbstractItemModel
{
    Q_OBJECT
private:
    QVector<Answer> _data;
public:
    explicit TableModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent) override;
    QVariant selectedRowData(const QItemSelection &selected);
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
public slots:
    void addValue(const Answer &value);
    void deleteValues(const QItemSelection &selected);
};

#endif // TABLEMODEL_H
