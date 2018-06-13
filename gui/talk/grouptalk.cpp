#include "grouptalk.h"
#include "messageitem.h"
#include "messagerecord.h"
#include "talkwarntip.h"
#include "ui_grouptalk.h"

#include "talkmanage.h"
#include "expressionwidget.h"

#include <QScrollBar>
#include <QTimer>
#include <QToolButton>
#include <windowimpl.h>

#define E_M ExpresssionManage::manage()
#define F_M FontManage::manage()

class GroupTalkPrivate : public WindowImpl
{
public:
    GroupTalkPrivate(GroupTalk *parent)
        :WindowImpl(parent)
        ,p(parent)
        ,maxItemCount(100)
    {
        voiceAnimationColor.append(QColor(0,255,0));
        voiceAnimationColor.append(QColor(0,85,0));
    }

    void init()
    {
        p->ui->setupUi(p);

        voiceAnimationTimer.setSingleShot(false);
        voiceAnimationTimer.setInterval(1000);

        QObject::connect(&voiceAnimationTimer,SIGNAL(timeout()),p,SLOT(recordingVoice()));

        p->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
        p->setAttribute(Qt::WA_TranslucentBackground);
        p->setAttribute(Qt::WA_Mapped);
        p->setMouseTracking(true);

        p->ui->tool->installEventFilter(p);

        QToolButton *send = new QToolButton;
        send->setPopupMode(QToolButton::MenuButtonPopup);
        send->setIcon(QIcon(":/res/talk/okl.png"));
        send->setFixedSize(55,35);
        QAction *a = p->ui->tool->insertWidget(p->ui->actionVoice,send);
        a->setVisible(true);
        QList<QAction *> list;
        QAction *local = new QAction("Send Local Pictures");
        list.append(local);
        send->addActions(list);
        QObject::connect(send,SIGNAL(clicked()),p,SLOT(selectLocalPicture()));

        /* Screenshot. */
        QToolButton *screenshot = new QToolButton;
        screenshot->setPopupMode(QToolButton::MenuButtonPopup);
        screenshot->setFixedSize(55,35);
        a = p->ui->tool->insertWidget(p->ui->actionMusic,screenshot);
        a->setVisible(true);
        list.clear();
        a = new QAction("Screenshot Ctrl+ATL+A");
        list.append(a);
        a = new QAction("Hide this window when capturing.");
        list.append(a);
        screenshot->addActions(list);
        QObject::connect(screenshot,SIGNAL(clicked()),p,SLOT(selectLocalPicture()));

        /* Font setting init. */
        p->ui->font_setting->setVisible(false);

        /* Voice widget init. */
        p->ui->voice->setVisible(false);

        /* Warn tip widget init. */
        tip = new TalkWarnTip(p->ui->msg_display);
        tip->setVisible(false);

        record = new MessageRecord;

        /* when init, set font_select hide. */
        p->ui->font_select->hide();

        p->ui->splitter->setStretchFactor(0,7);
        p->ui->splitter->setStretchFactor(1,1);

        /* init msg display. */
        p->ui->msg_display->setScene(new QGraphicsScene);
        p->ui->msg_display->installEventFilter(p);

        /* more tips. */
        more = new MessageMoreItem;
        more->setScene(p->ui->msg_display->scene());
    }

    void msgDisplayEvent(QEvent *event)
    {
        QGraphicsItem *clickedItem = 0;
        QWidget *w = p->ui->msg_display->viewport();
        switch(event->type())
        {
        case QEvent::MouseButtonPress:
            clickedItem = p->ui->msg_display->itemAt(w->mapFromGlobal(QCursor::pos()));
            if(clickedItem)
            {
                qDebug() << "item clicked";
                emit p->headClicked(clickedItem->data(AbstractMessageItem::Name).toString());
            }
            break;
        default:
            break;
        }
    }

    void voiceRecordDone()
    {
        voiceAnimationTimer.stop();
        voiceTime = 0;
        p->ui->send->setEnabled(false);
        p->ui->voice->setVisible(false);
        p->ui->voice->setValue(0);
    }

    void updateMessageItems()
    {
        qreal height = 0;
        qreal h = 0;
        int count = 0;
        if(items.count())
        {
            more->setItemWidth(p->ui->msg_display->width());
            more->setPos(QPointF(0,height));

            height+=more->boundingRect().height();
            h+= more->boundingRect().height();

            qDebug() << "more:" << more->boundingRect();
        }

        int itemWidth = p->ui->msg_display->width()-10-p->ui->msg_display->verticalScrollBar()->width();
        foreach(AbstractMessageItem *item,items)
        {
            qDebug() << "item" << item->boundingRect() << items.count();
            item->setItemWidth(itemWidth);
            item->setPos(QPointF(0,height));

            height+=item->boundingRect().height();
            h+= item->boundingRect().height();
            count++;
            if(count==maxItemCount)
                break;
        }
        p->ui->msg_display->setSceneRect(0,0,p->ui->msg_display->width(),h);
        update();
    }

    bool toolEvent(QEvent *event)
    {
        if(event->type()==QEvent::HoverEnter || event->type()==QEvent::HoverMove)
        {
            QPoint pos = p->ui->tool->mapFromGlobal(QCursor::pos());
            if(p->ui->tool->actionAt(pos)==p->ui->actionExpression && !p->ui->actionExpression->isChecked())
            {
                E_M->expression->hide();
                E_M->history->show(p->ui->tool->mapToGlobal(QPoint(0,5)));
            }
            else
                E_M->history->hide();
        }
        else if(event->type()==QEvent::HoverLeave)
        {
            if(!E_M->history->rect().contains(E_M->history->mapFromGlobal(QCursor::pos())))
                E_M->history->hide();
        }
        return false;
    }

    GroupTalk *p;
    QTimer voiceAnimationTimer;
    QList<QColor> voiceAnimationColor;
    int voiceAnimationTimerInterval;
    int voiceTimeLimit;
    int voiceTime;
    TalkWarnTip *tip;
    MessageRecord *record;

    QList<AbstractMessageItem *> items;
    MessageMoreItem *more;
    int maxItemCount;
};

GroupTalk::GroupTalk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupTalk),
    p_d(new GroupTalkPrivate(this))
{
    p_d->init();
}

GroupTalk::~GroupTalk()
{
    delete p_d;
    delete ui;
}

void GroupTalk::appendItem(AbstractMessageItem *item)
{
    p_d->items.append(item);
    item->setScene(ui->msg_display->scene());
    updateMessageItems();
}

void GroupTalk::appendItems(const QList<AbstractMessageItem *> &items)
{
    p_d->items.append(items);

    foreach(AbstractMessageItem *item,items)
        item->setScene(ui->msg_display->scene());

    updateMessageItems();
}

void GroupTalk::prependItem(AbstractMessageItem *item)
{
    p_d->items.prepend(item);
    item->setScene(ui->msg_display->scene());
    updateMessageItems();
}

void GroupTalk::prependItems(const QList<AbstractMessageItem *> &items)
{
    foreach(AbstractMessageItem *item,items)
    {
        p_d->items.prepend(item);
        item->setScene(ui->msg_display->scene());
    }

    updateMessageItems();
}

void GroupTalk::removeItem(AbstractMessageItem *item)
{
    p_d->items.removeAll(item);
    updateMessageItems();
}

void GroupTalk::setMaxCount(int count)
{
    p_d->maxItemCount = count;
    updateMessageItems();
}

int GroupTalk::maxCount() const
{
    return p_d->maxItemCount;
}

void GroupTalk::updateMessageItems()
{
}

bool GroupTalk::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==ui->msg_display)
        p_d->msgDisplayEvent(event);

    return QWidget::eventFilter(watched,event);
}
