#include "abstractitem.h"
#include "abstractitemdata.h"


class AbstractItemPrivate
{
public:
    AbstractItemPrivate(AbstractItemData *d)
        :ref(1)
        ,data(d)
        ,listItem(0)
        ,treeItem(0)
    {}

    int ref;
    AbstractItemData *data;
    QListWidgetItem* listItem;
    QTreeWidgetItem *treeItem;
};

AbstractItem::AbstractItem(const AbstractItem &item)
{
    p_d = item.p_d;
    p_d->ref++;
}

AbstractItem::~AbstractItem()
{
    p_d->ref--;
    if(!p_d->ref)
        delete p_d;
}

void AbstractItem::requestMenu(QMenu *menu)
{
    Q_UNUSED(menu)
}

QListWidgetItem *AbstractItem::listItem()
{
    return p_d->listItem;
}

void AbstractItem::setListItem(QListWidgetItem *item)
{
    p_d->listItem = item;
}

QTreeWidgetItem *AbstractItem::treeItem()
{
    return p_d->treeItem;
}

void AbstractItem::setTreeItem(QTreeWidgetItem *item)
{
    p_d->treeItem = item;
}

AbstractItem::AbstractItem(AbstractItemData *d)
    :p_d(new AbstractItemPrivate(d))
{
}

void AbstractItem::setData(AbstractItemData *data)
{
    p_d->data = data;
}

AbstractItemData *AbstractItem::data() const
{
    return p_d->data;
}
