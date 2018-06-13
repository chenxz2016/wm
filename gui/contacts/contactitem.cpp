#include "contactitem.h"
#include "ui_contactitem.h"

#include <QMouseEvent>

class ContactItemPrivate
{
public:
    ContactItemPrivate()
        :m_selectEnlarge(true)
        ,m_iconSize(30,30)
        ,m_iconEnlargeSize(45,45)
    {}
    bool m_selectEnlarge;
    QSize m_iconSize;
    QSize m_iconEnlargeSize;
};

ContactItem::ContactItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactItem)
{
    ui->setupUi(this);
}

ContactItem::~ContactItem()
{
    delete ui;
}

bool ContactItem::selectEnlarge() const
{
    return p_d->m_selectEnlarge;
}

void ContactItem::setSelectEnlarge(bool enlarge)
{
    p_d->m_selectEnlarge = enlarge;
    update();
}

QSize ContactItem::iconSize() const
{
    return p_d->m_iconSize;
}

void ContactItem::setIconSize(const QSize &size)
{
    p_d->m_iconSize = size;
    update();
}

QSize ContactItem::iconEnlargeSize() const
{
    return p_d->m_iconEnlargeSize;
}

void ContactItem::setIconEnlargeSize(const QSize &size)
{
    p_d->m_iconEnlargeSize = size;
    update();
}

void ContactItem::resizeEvent(QResizeEvent *event)
{
    ui->icon->setFixedSize(event->size().height()-10,event->size().height()-10);
    QWidget::resizeEvent(event);
}
