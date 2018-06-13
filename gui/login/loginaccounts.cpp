#include "loginaccounts.h"

#include "ui_loginaccountitem.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QBitmap>


static QPixmap pixmap_to_round(const QPixmap &src, int radius)
{
    if (src.isNull()) {
        return QPixmap();
    }

    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);

    QPixmap image = src.scaled(size);
    image.setMask(mask);

    return image;
}

class LoginAccountItemPrivate
{
public:
    LoginAccountItemPrivate(LoginAccountItem *p,QWidget *v)
        :parent(p)
    {
        view = dynamic_cast<LoginAccountView *>(v);
        if(view)
            bgColor = view->color();
        else
            bgColor = Qt::white;
    }

    void restore_animation()
    {
        QPropertyAnimation *a = new QPropertyAnimation(parent,"size");
        a->setDuration(100);
        a->setStartValue(QSize(parent->width(),view->hoverHeight()));
        a->setEndValue(QSize(parent->width(),view->itemHeight()));
        a->start(QAbstractAnimation::DeleteWhenStopped);
    }

    void enlarg_animation()
    {
        QPropertyAnimation *a = new QPropertyAnimation(parent,"size");
        a->setDuration(100);
        a->setStartValue(QSize(parent->width(),view->itemHeight()));
        a->setEndValue(QSize(parent->width(),view->hoverHeight()));
        a->start(QAbstractAnimation::DeleteWhenStopped);
    }

    QColor bgColor;
    QString password;
    LoginAccountItem *parent;
    LoginAccountView *view;
};

LoginAccountItem::LoginAccountItem(QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::LoginAccountItem)
    ,p_d(new LoginAccountItemPrivate(this,parent))
{
    ui->setupUi(this);
    ui->remove->setVisible(false);
    setAttribute(Qt::WA_MouseTracking);

    resize(QSize(p_d->view->width(),p_d->view->itemHeight()));
}

LoginAccountItem::~LoginAccountItem()
{
    delete p_d;
}

QPixmap LoginAccountItem::icon() const
{
    return QPixmap(*ui->icon->pixmap());
}

void LoginAccountItem::setIcon(const QPixmap &pixmap)
{
    ui->icon->setPixmap(pixmap_to_round(pixmap,ui->icon->width()/2));
}

QString LoginAccountItem::accountName() const
{
    return ui->name->text();
}

void LoginAccountItem::setAccountName(const QString &name)
{
    ui->name->setText(name);
}

QString LoginAccountItem::accountID() const
{
    return ui->id->text();
}

void LoginAccountItem::setAccountID(const QString id)
{
    ui->id->setText(id);
}

QString LoginAccountItem::accountPWD() const
{
    return p_d->password;
}

void LoginAccountItem::setAccountPWD(const QString &pwd)
{
    p_d->password = pwd;
}

void LoginAccountItem::resizeEvent(QResizeEvent *event)
{
    ui->icon->setFixedSize(QSize(height(),height()));
    if(p_d->view)
    {
        setFixedWidth(p_d->view->width());
        p_d->view->updateGeometry();
    }
    QWidget::resizeEvent(event);
}

void LoginAccountItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(p_d->parent)
        painter.fillRect(rect(),p_d->bgColor);

    QWidget::paintEvent(event);
}

void LoginAccountItem::enterEvent(QEvent *event)
{
    p_d->bgColor = p_d->view->hoverColor();
    ui->name->setVisible(true);
    ui->id->setStyleSheet("color:white");
    ui->remove->setVisible(true);
    p_d->enlarg_animation();
    update();
    QWidget::enterEvent(event);
}

void LoginAccountItem::leaveEvent(QEvent *event)
{
    p_d->bgColor = p_d->view->color();
    ui->id->setStyleSheet("color:black");
    ui->remove->setVisible(false);
    ui->name->setVisible(false);
    p_d->restore_animation();
    update();
    QWidget::leaveEvent(event);
}


class LoginAccountViewPrivate
{
public:
    LoginAccountViewPrivate(LoginAccountView *p)
        :hoverHeight(45)
        ,hieght(20)
        ,itemHieght(25)
        ,color(Qt::white)
        ,hoverColor(Qt::blue)
        ,parent(p)
    {}
    int hoverHeight;
    int hieght;
    int itemHieght;
    QMap<QString,LoginAccountItem *> itemMap;
    QColor color;
    QColor hoverColor;

    LoginAccountView *parent;
};

LoginAccountView::LoginAccountView(QWidget *parent)
    :QWidget(parent)
    ,p_d(new LoginAccountViewPrivate(this))
{
    setAttribute(Qt::WA_MouseTracking);
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
}

LoginAccountView::~LoginAccountView()
{
    delete p_d;
}

void LoginAccountView::appendAccount(LoginAccountItem *item)
{
    if(!p_d->itemMap.contains(item->accountID()))
    {
        connect(item,SIGNAL(deleteRequest(LoginAccountItem *)),this,SLOT(removeItem(LoginAccountItem *)));
        p_d->itemMap[item->accountID()] = item;
        updateGeometry();
    }
}

void LoginAccountView::removeAccount(LoginAccountItem *item)
{
    if(p_d->itemMap.contains(item->accountID()))
        p_d->itemMap.remove(item->accountID());
}

void LoginAccountView::removeAccount(const QString &id)
{
    if(p_d->itemMap.contains(id))
    {
        delete p_d->itemMap[id];
        updateGeometry();
        p_d->itemMap.remove(id);
    }
}

int LoginAccountView::hoverHeight() const
{
    return p_d->hoverHeight;
}

void LoginAccountView::setHoverHeight(int height)
{
    p_d->hoverHeight = height;
}

void LoginAccountView::setItemHeight(int height)
{
    p_d->itemHieght = height;
}

int LoginAccountView::itemHeight() const
{
    return p_d->itemHieght;
}

void LoginAccountView::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void LoginAccountView::mouseReleaseEvent(QMouseEvent *event)
{
    LoginAccountItem *item = dynamic_cast<LoginAccountItem *>(childAt(event->pos()));
    if(item)
        emit itemSelected(item);

    QWidget::mouseReleaseEvent(event);
}

void LoginAccountView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(),Qt::white);
    QWidget::paintEvent(event);
}

void LoginAccountView::removeItem(LoginAccountItem *item)
{
    p_d->itemMap.remove(item->accountID());
}

QColor LoginAccountView::hoverColor() const
{
    return p_d->hoverColor;
}

void LoginAccountView::setHoverColor(const QColor &color)
{
    p_d->hoverColor = color;
    update();
}

QColor LoginAccountView::color() const
{
    return p_d->color;
}

void LoginAccountView::setColor(const QColor &color)
{
    p_d->color = color;
    update();
}

void LoginAccountView::updateGeometry()
{
    QList<LoginAccountItem *> list = p_d->itemMap.values();
    int y=0;
    foreach(LoginAccountItem *item,list)
    {
        item->move(0,y);
        y += item->height();
    }
}

void LoginAccountItem::on_remove_clicked()
{
    emit deleteRequest(this);
}
