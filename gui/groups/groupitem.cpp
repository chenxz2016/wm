#include "groupitem.h"
#include "ui_multitalkitem.h"
#include "ui_groupitem.h"

#include <QDebug>
#include <QMouseEvent>

class GroupItemPrivate
{
public:
    GroupItemPrivate()
        :m_mailLinkEnable(true)
        ,m_selectEnlarge(true)
        ,m_iconSize(40,40)
        ,m_iconEnlargeSize(60,60)
        ,m_mailLinkRect(366,19,25,20)
    {}
    bool m_mailLinkEnable;
    bool m_selectEnlarge;
    QSize m_iconSize;
    QSize m_iconEnlargeSize;
    QRect m_mailLinkRect;
};

GroupItem::GroupItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupItem)
{
    ui->setupUi(this);
    p_d = new GroupItemPrivate;
    ui->mail->setVisible(false);
}

GroupItem::~GroupItem()
{
    delete ui;
    delete p_d;
}

bool GroupItem::mailLinkEnable() const
{
    return p_d->m_mailLinkEnable;
}

void GroupItem::setMailLinkEnable(bool enable)
{
    p_d->m_mailLinkEnable = enable;
    update();
}

bool GroupItem::selectEnlarge() const
{
    return p_d->m_selectEnlarge;
}

void GroupItem::setSelectEnlarge(bool enlarge)
{
    p_d->m_selectEnlarge = enlarge;
    update();
}

QSize GroupItem::iconSize() const
{
    return p_d->m_iconSize;
}

void GroupItem::setIconSize(const QSize &size)
{
    p_d->m_iconSize = size;
    update();
}

QSize GroupItem::iconEnlargeSize() const
{
    return p_d->m_iconEnlargeSize;
}

void GroupItem::setIconEnlargeSize(const QSize &size)
{
    p_d->m_iconEnlargeSize = size;
    update();
}

void GroupItem::mouseMoveEvent(QMouseEvent *event)
{
    if(p_d->m_mailLinkRect.contains(event->pos()))
    {
        ui->mail->setVisible(true);
    }
    else
    {
        ui->mail->setVisible(false);
    }
    QWidget::mouseMoveEvent(event);
}

void GroupItem::resizeEvent(QResizeEvent *event)
{
    qDebug() << "resize";
    int w = width();
    int h = height();
    int x = (w-ui->mail->width()-5);
    int y = (h-ui->mail->height()-10)/2;
    ui->icon->setFixedSize(event->size().height()-10,event->size().height()-10);
    p_d->m_mailLinkRect = QRect(x,y,ui->mail->width(),ui->mail->height());
    QWidget::resizeEvent(event);
}

class MultiTalkItemPrivate
{
public:
    MultiTalkItemPrivate()
        :m_selectEnlarge(true)
        ,m_iconSize(30,30)
        ,m_iconEnlargeSize(45,45)
    {}
    bool m_selectEnlarge;
    QSize m_iconSize;
    QSize m_iconEnlargeSize;
};


MultiTalkItem::MultiTalkItem(QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::MultiTalkItem)
{
    ui->setupUi(this);
    p_d = new MultiTalkItemPrivate;
}

MultiTalkItem::~MultiTalkItem()
{
    delete ui;
    delete p_d;
}

bool MultiTalkItem::selectEnlarge() const
{
    return p_d->m_selectEnlarge;
}

void MultiTalkItem::setSelectEnlarge(bool enlarge)
{
    p_d->m_selectEnlarge = enlarge;
}

QSize MultiTalkItem::iconSize() const
{
    return p_d->m_iconSize;
}

void MultiTalkItem::setIconSize(const QSize &size)
{
    p_d->m_iconSize = size;
    update();
}

QSize MultiTalkItem::iconEnlargeSize() const
{
    return p_d->m_iconEnlargeSize;
}

void MultiTalkItem::setIconEnlargeSize(const QSize &size)
{
    p_d->m_iconEnlargeSize = size;
    update();
}

void MultiTalkItem::resizeEvent(QResizeEvent *event)
{
    ui->icon->setFixedSize(event->size().height()-10,event->size().height()-10);
    if(p_d->m_selectEnlarge && height()>=40)
    {
        ui->name->setAlignment(Qt::AlignBottom|Qt::AlignLeft);
        ui->number->setAlignment(Qt::AlignBottom|Qt::AlignLeft);
        ui->time->setAlignment(Qt::AlignBottom|Qt::AlignLeft);
        ui->message->setVisible(true);
    }
    else
    {
        ui->name->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
        ui->number->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
        ui->time->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
        ui->message->setVisible(false);
    }
    QWidget::resizeEvent(event);
}
