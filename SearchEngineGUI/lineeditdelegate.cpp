#include "lineeditdelegate.h"

#include <QEvent>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPainter>

LineEditDelegate::LineEditDelegate(QObject *parent) : QItemDelegate(parent)
{

}

QWidget *LineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void LineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *lEdit = qobject_cast<QLineEdit*>(editor);
    lEdit->setText(value);
}

void LineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lEdit = qobject_cast<QLineEdit*>(editor);
    QString text = lEdit->text();
    model->setData(index, text);

}

void LineEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect r = option.rect;
    r.setWidth(r.width() - 25);
    editor->setGeometry(r);
    qDebug() << r;
}

bool LineEditDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    qDebug() << "EDITOR EVENT";
     QRect r(option.rect.width()-20, option.rect.y(), 20, 20);
     if (event->type() == QEvent::MouseButtonPress) {
      pressPos = static_cast <QMouseEvent*> (event)->pos();
      qDebug() << "MOUSE PRESS";
      return r.contains(pressPos);
     }
     else if(event->type() == QEvent::MouseButtonRelease) {
         qDebug() << "MOUSE RELEASE";
         QPoint releasePos = static_cast <QMouseEvent*> (event)->pos();
        if (r.contains(pressPos) && r.contains(releasePos)) {
        emit del(index);
      return true;
      }
     }
     return false;
}

void LineEditDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect r = option.rect;
     if (option.state & QStyle::State_Selected) {
      painter->fillRect(r, QColor(200, 200, 200));
     }
     painter->save();
     QString data = index.model()->data(index).toString();
     painter->setBrush(option.palette.text());
     painter->drawText(r, Qt::AlignVCenter, data);
     //QPixmap delPixmap("del.png");
     //painter->drawPixmap(r.width() - 20, r.y(), 20, 20, delPixmap);
     painter->restore();
}

QSize LineEditDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.width(), 20);
}
