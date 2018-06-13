#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

class AbstractItemData;
class QMenu;
class QListWidgetItem;
class QTreeWidgetItem;

class AbstractItem
{
public:
    AbstractItem(const AbstractItem &item);
    virtual ~AbstractItem();

    virtual void requestMenu(QMenu *menu);

    QListWidgetItem* listItem();
    void setListItem(QListWidgetItem* item);

    QTreeWidgetItem *treeItem();
    void setTreeItem(QTreeWidgetItem *item);
protected:
    AbstractItem(AbstractItemData *d = 0);

    void setData(AbstractItemData *data);
    AbstractItemData *data()const;
private:
    class AbstractItemPrivate *p_d;
};

#endif // ABSTRACTITEM_H
