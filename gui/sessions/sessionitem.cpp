#include "sessionitem.h"

#include "abstractitemdata.h"
#include "mainwindow.h"
#include "ui_sessionitem.h"

#include <QMenu>
#include <QDebug>
#include <QTimer>
#include <briefcard.h>
#include <QListWidget>
#include "show/wmshow.h"
#include "hide/wmhide.h"


class SessionItemData : public AbstractItemData
{
public:
    SessionItemData(){}
};

static int num = 0;

class BriefCardManage
{
public:
    static BriefCard *instance()
    {
        if(!card)
            card = new BriefCard;
        return card;
    }

private:
    static BriefCard *card;
};

BriefCard *BriefCardManage::card = 0;


class SessionItemPrivate
{
public:
    SessionItemPrivate(SessionItem *parent)
        :p(parent)
        ,m_stick(new QAction("Stick"))
        ,m_status(0)
        ,m_iconPath(":/res/icon.jpg")
        ,window(0)
    {}

    void init()
    {
        p->ui->setupUi(p);
        p->ui->icon->installEventFilter(p);
        p->ui->name->setText(QString("%1").arg(num++));

        BriefCardManage::instance()->installEventFilter(p);

        timer.setSingleShot(true);
        timer.setInterval(500);
        QObject::connect(&timer,SIGNAL(timeout()),p,SLOT(hideCard()));
        QObject::connect(BriefCardManage::instance(),SIGNAL(requestHide()),p,SLOT(hideCard()));
    }

    void iconEvent(QEvent *event)
    {
        int x;
        int y;
        switch(event->type())
        {
        case QEvent::Enter:
            y = p->mapToGlobal(p->rect().topRight()).y();
            x = window->mapToGlobal(window->rect().topRight()).x();
            WMAnimation::show_by_pos(BriefCardManage::instance(),200,QPointF(x,y-20),QPointF(x,y));
            break;
        case QEvent::Leave:
            timer.start();
            break;
        default:
            break;
        }
    }

    void briefEvent(QEvent *event)
    {
        switch(event->type())
        {
        case QEvent::Enter:
            timer.stop();
            break;
        case QEvent::Leave:
            timer.start();
            break;
        default:
            break;
        }
    }


    SessionItem *p;
    QAction *m_stick;
    int m_status;
    QString m_iconPath;
    QDateTime m_time;
    MainWindow *window;
    QTimer timer;
};

SessionItem::SessionItem(QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::SessionItem)
    ,p_d(new SessionItemPrivate(this))
{
    p_d->init();

    p_d->window = dynamic_cast<MainWindow *>(parent);
}

SessionItem::~SessionItem()
{
    delete ui;
    delete p_d;
}


QString SessionItem::iconPath() const
{
    return p_d->m_iconPath;
}

void SessionItem::setIconPath(const QString &path)
{
    p_d->m_iconPath = path;
    ui->icon->setStyleSheet(QString("QWidget#icon{border-radius:20;"
                                    "border-image: url(%1);}").arg(path));
}

QString SessionItem::describeName() const
{
    return ui->name->text();
}

void SessionItem::setDescribeName(const QString &name)
{
    ui->name->setText(name);
}

QString SessionItem::lastMessage() const
{
    return ui->lastMessage->text();
}

void SessionItem::setLastMessage(const QString &message)
{
    ui->lastMessage->setText(message);
}

QDateTime SessionItem::lastTime() const
{
    return QDateTime::fromString(ui->time->text());
}

void SessionItem::setLastTime(const QDateTime &time)
{
    ui->time->setText(time.toString());
}

void SessionItem::setStatus(int status)
{
    p_d->m_status = status;
}

int SessionItem::status() const
{
    return p_d->m_status;
}

void SessionItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "double clicked";
    emit requestSessionWindow();
    if(p_d->window)
    {
        p_d->window->openSessionWindow(this);
    }
    QWidget::mouseDoubleClickEvent(event);
}

bool SessionItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==ui->icon)
        p_d->iconEvent(event);

    if(watched==BriefCardManage::instance())
        p_d->briefEvent(event);
    return QWidget::eventFilter(watched,event);
}

bool SessionItem::event(QEvent *event)
{
    if(event->type()==QEvent::ParentChange)
    {
        if(parentWidget())
        {}
        else
        {}
    }
    return QWidget::event(event);
}

void SessionItem::hideCard()
{
    WMAnimation::hide_by_pos(BriefCardManage::instance(),80,\
                             BriefCardManage::instance()->pos(),
                             QPointF(BriefCardManage::instance()->x(),BriefCardManage::instance()->y()-30));
}


