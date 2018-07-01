#include "contactview.h"
#include "viewdelegate.h"
#include <QDebug>
#include <wmp_user.h>

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
    QMap<QString,QVariant> map = d.toMap();
    quint32 id = map["id"].toInt();
    quint16 user_friend_attr = map["user_friend_attr"].toInt();
    QString team_name = map["team_name"].toString();
    quint16 team_index = map["team_index"].toInt();

    switch(id)
    {
    case WMP_USER_ADD_ID:
    case WMP_USER_DEL_ID:
    case WMP_USER_SET_ID:
    case WMP_USER_MSG_ID:
        break;
    case WMP_USER_FRIEND_ID:
    {

        switch(user_friend_attr)
        {
        case WMP_USER_FRIEND_LIST_REQ:
        case WMP_USER_FRIEND_LIST_RSP:
        {
            QList<QVariant> list = map["user_friend_list"].toList();
            QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(team_name));
            addTopLevelItem(item);
            QList<QTreeWidgetItem *> l;
            foreach(QVariant i , list)
            {
                QTreeWidgetItem *c = new QTreeWidgetItem(QStringList(QString("asdasda"/*i.toInt()*/)));
                l.append(c);
            }
            item->addChildren(l);
            break;
        }
        case WMP_USER_FRIEND_NUM_REQ:
        case WMP_USER_FRIEND_NUM_RSP:
            reset();
            break;
        default:
            break;
        }

        break;
    }
    case WMP_USER_FIND_ID:
    case WMP_USER_FETCH_ID:
    default:
        break;
    }
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
