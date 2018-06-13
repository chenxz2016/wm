#include "sessionitem.h"
#include "sessionview.h"

#include <QAction>
#include <QMenu>
#include <QDebug>

class SessionViewPrivate
{
public:
    SessionViewPrivate()
        :m_stick(new QAction("Stick"))
        ,m_cancelStick(new QAction("Cancel Stick"))
        ,m_remove(new QAction("Remove From Session List"))
    {}

    QAction *m_stick;
    QAction *m_cancelStick;
    QAction *m_remove;
};

SessionView::SessionView(QWidget *parent)
    :QListWidget(parent)
{
    p_d = new SessionViewPrivate;
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(popMenu(QPoint)));

    connect(p_d->m_stick,SIGNAL(triggered(bool)),this,SLOT(stick(bool)));
    connect(p_d->m_cancelStick,SIGNAL(triggered(bool)),this,SLOT(cancelStick(bool)));
    connect(p_d->m_remove,SIGNAL(triggered(bool)),this,SLOT(removeItem(bool)));
}

SessionView::~SessionView()
{
    delete p_d;
}

void SessionView::stick(bool)
{
    QListWidgetItem *item = itemAt(mapFromGlobal(QCursor::pos()));
    if(!item)
        return ;

    int r = row(item);
    qDebug() << "row:" << r;
    if(!r)
        return ;

    QList<QWidget *> list;
    for(int i=0;i<=r;i++)
    {
        SessionItem *item = dynamic_cast<SessionItem *>(itemWidget(this->item(i)));
        if(item)
            list.append(new SessionItem(item));
    }
    for(int i=0;i<=r;i++)
    {
        delete this->takeItem(0);
    }

    foreach(QWidget *w,list)
    {
        QListWidgetItem *item = new QListWidgetItem;
        insertItem(0,item);
        setItemWidget(item,w);
    }
    qDebug() << "swap success";
}

void SessionView::cancelStick(bool)
{

}

void SessionView::popMenu(QPoint point)
{
    QList<QAction *> list;


    QMenu menu;
    QListWidgetItem *item = itemAt(point);
    QWidget *widget = itemWidget(item);
    SessionItem *i = dynamic_cast<SessionItem *>(widget);
    if(i)
    {
        if(!i->status())
        {
            list.append(p_d->m_stick);
        }
        else
        {
            list.append(p_d->m_cancelStick);
        }
        list.append(p_d->m_remove);
    }
    menu.exec(list,mapToGlobal(point));
}

void SessionView::removeItem(bool)
{
    QList<QListWidgetItem *> list = selectedItems();
    foreach(QListWidgetItem *item,list)
        delete this->takeItem(row(item));
}
