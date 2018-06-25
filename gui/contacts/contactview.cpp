#include "contactview.h"
#include "viewdelegate.h"

ContactView::ContactView(QWidget *parent)
    :QTreeWidget(parent)
{
    setItemDelegate(new ViewDelegate(this));

    connect(this,SIGNAL(clicked(QModelIndex)),this,SLOT(contactViewItemClicked(QModelIndex)));
    connect(this,SIGNAL(itemExpanded(QTreeWidgetItem*)),this,SLOT(contactViewItemExpland(QTreeWidgetItem*)));
    connect(this,SIGNAL(itemCollapsed(QTreeWidgetItem*)),this,SLOT(contactViewItemExpland(QTreeWidgetItem*)));
}

ContactView::~ContactView()
{

}

void ContactView::appendContacts(const QVariant &d)
{
    Q_UNUSED(d)
}

void ContactView::update()
{
    updateGeometries();
    QTreeWidget::update();
}

void ContactView::contactViewItemExpland(QTreeWidgetItem *item)
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

void ContactView::contactViewItemClicked(QModelIndex index)
{
    if(index.isValid())
    {
        QMap<QString,QVariant> map = index.data(ViewDataRole).toMap();
        if(map["type"].toInt()!=ContactItemRole)
        {
            return ;
        }
    }
    if(m_index.isValid())
    {
        QMap<QString,QVariant> map = m_index.data(ViewDataRole).toMap();
        map["select_flag"] = false;
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
