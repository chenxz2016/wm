#include "viewdelegate.h"

#include <QDebug>

ViewDelegate::ViewDelegate(QWidget *parent)
    :QStyledItemDelegate(parent)
{
    m_parent = parent;
}

ViewDelegate::~ViewDelegate()
{

}

void ViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter,option,index);
}

QSize ViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int width = m_parent->property("width").toInt();
    QSize size =  QStyledItemDelegate::sizeHint(option,index);

    QMap<QString,QVariant> map;
    switch(index.data(ViewRole).toInt())
    {
    case GroupRole:
        map = index.data(ViewDataRole).toMap();
        switch(map["type"].toInt())
        {
        case GroupRootRole:
            size.setHeight(GROUP_ROOT_HEIGHT);
            break;
        case GroupItemRole:
            size.setWidth(width);
            size.setHeight(20);
            if(map["select_enlarge"].toBool() && map["select_flag"].toBool())
            {
                qDebug() << "set height";
                size.setHeight(GROUP_ITEM_HEIGHT);
            }
            break;
        }
        break;
    case ContactRole:
        map = index.data(ViewDataRole).toMap();
        switch(map["type"].toInt())
        {
        case ContactRootRole:
            size.setHeight(CONTACT_ROOT_HEIGHT);
            break;
        case ContactItemRole:
            size.setWidth(width);
            size.setHeight(CONTACT_ROOT_HEIGHT);
            if(map["select_enlarge"].toBool() && map["select_flag"].toBool())
            {
                size.setHeight(CONTACT_ITEM_HEIGHT);
            }
            break;
        }
        break;
    default:
        size = QStyledItemDelegate::sizeHint(option,index);
    }
    qDebug() << "size:" << size;
    return size;
}

QWidget *ViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::createEditor(parent,option,index);
}

void ViewDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QStyledItemDelegate::setEditorData(editor,index);
}

void ViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QStyledItemDelegate::setModelData(editor,model,index);
}
