#include "groupview.h"
#include "viewdelegate.h"
#include <QDebug>

GroupView::GroupView(QWidget *parent)
    :QTreeWidget(parent)
{
    setItemDelegate(new ViewDelegate(this));
    connect(this,SIGNAL(clicked(QModelIndex)),this,SLOT(groupsViewItemClicked(QModelIndex)));
    connect(this,SIGNAL(itemExpanded(QTreeWidgetItem*)),this,SLOT(groupsViewItemExpland(QTreeWidgetItem*)));
    connect(this,SIGNAL(itemCollapsed(QTreeWidgetItem*)),this,SLOT(groupsViewItemExpland(QTreeWidgetItem*)));

}

void GroupView::update()
{
    updateGeometries();
}

void GroupView::appendGroups(const QVariant &d)
{
    QTreeWidgetItem *root = new QTreeWidgetItem(QStringList(QString("My Groups")));

    QList<QVariant> list = d.toMap()["group_list"].toList();
    foreach (QVariant i, list)
    {
        root->addChild(new QTreeWidgetItem(QStringList(QString::number(i.toInt()))));
    }
}

void GroupView::groupsViewItemExpland(QTreeWidgetItem *item)
{
    if(!item->isExpanded())
    {
        item->setIcon(0,QIcon(":/res/pds.png"));
    }
    else
    {
        item->setIcon(0,QIcon(":/res/pdt.png"));
    }
}

void GroupView::groupsViewItemClicked(QModelIndex index)
{
    if(index.isValid())
    {
        QMap<QString,QVariant> map = index.data(ViewDataRole).toMap();
        if(map["type"].toInt()!=GroupItemRole)
        {
            return ;
        }
    }
    if(m_index.isValid())
    {
        QMap<QString,QVariant> map = m_index.data(ViewDataRole).toMap();
        map["select_flag"] = false;
        qDebug() << "select false" << map;
        if(indexWidget(m_index))
        {
            QSize size = indexWidget(m_index)->size();
            size.setHeight(35);
            indexWidget(m_index)->resize(size);
        }
        model()->setData(m_index,map,ViewDataRole);
    }
    m_index = index;
    if(index.isValid())
    {
        QMap<QString,QVariant> map = index.data(ViewDataRole).toMap();
        map["select_flag"] = true;
        model()->setData(index,map,ViewDataRole);
        if(indexWidget(index))
        {
            QSize size = indexWidget(index)->size();
            size.setHeight(50);
            indexWidget(index)->resize(size);
        }
    }
    updateGeometries();
}
