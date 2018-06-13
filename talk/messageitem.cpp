#include "messageitem.h"
#include "messageview.h"
#include "abstractbubble/abstractbubble.h"

#include <QStyleOptionGraphicsItem>
#include <QTextDocument>
#include <QMouseEvent>
#include <QPainter>
#include <QGraphicsView>
#include <QTextLayout>
#include <QTextBlock>
#include <QGraphicsVideoItem>
#include <QDateTime>

#include <audioitem/qgraphicsaudioitem.h>

QGraphicsMessageItem::QGraphicsMessageItem(QGraphicsItem *parent)
    :QGraphicsTextItem(parent)
{
    document()->setDocumentMargin(40);
    bubble = "example.bf";
}

QGraphicsMessageItem::QGraphicsMessageItem(const QString &text, QGraphicsItem *parent)
    :QGraphicsTextItem(text,parent)
{
}

void QGraphicsMessageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    QStyleOptionGraphicsItem op;
    op.initFrom(widget);

    op.state = QStyle::State_None;

    drawDecoration(painter);
    QGraphicsTextItem::paint(painter,&op,widget);
}

qreal QGraphicsMessageItem::margin() const
{
    return document()->documentMargin();
}

void QGraphicsMessageItem::setMargin(const qreal &m)
{
    document()->setDocumentMargin(m);
    update();
}

void QGraphicsMessageItem::drawDecoration(QPainter *painter)
{
    Q_UNUSED(painter)
    AbstractBubble *b = BubbleFactory::instance()->bubble(bubble);
    if(!b)
        return ;

    qreal dm = document()->documentMargin();
    QMarginsF m(dm,dm,dm,dm);
    QRectF r = boundingRect();
    QPixmap p = b->merge(r,m);
    painter->drawPixmap(r.toRect(),p,p.rect());
}

class MessageTextItemPrivate
{
public:
    MessageTextItemPrivate()
        :hm(5.0,3.0,3.0,5.0)
        ,mm(5.0,3.0,3.0,5.0)
        ,head(0)
        ,msg(0)
    {}

    virtual ~MessageTextItemPrivate()
    {
        if(head)
            delete head;
        if(msg)
            msg->deleteLater();
    }

    void init(const QPixmap &h, const QString &name, const QString &desc,const QList<QVariant> &msgs)
    {
        head = new QGraphicsPixmapItem(h.scaled(QSize(48,48),Qt::KeepAspectRatio,Qt::SmoothTransformation));
        head->setData(AbstractMessageItem::Type,"head");
        head->setData(AbstractMessageItem::Name,name);
        head->setData(AbstractMessageItem::Description,desc);
        head->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
        head->setCursor(Qt::PointingHandCursor);

        msg = new QGraphicsMessageItem;
        msg->setData(AbstractMessageItem::Type,"msg");

        msg->setTextInteractionFlags(Qt::TextSelectableByMouse);
        QTextCursor cursor = msg->textCursor();
        cursor.movePosition(QTextCursor::Start);
        foreach(QVariant d,msgs)
        {
            switch(d.type())
            {
            case QVariant::String:
                cursor.insertText(d.toString());
                break;
            case QVariant::Pixmap:
                cursor.insertImage(d.value<QPixmap>().toImage());
                break;
            default:
                break;
            }
        }
    }

    void init(const QPixmap &h, const QString &name, const QString &desc, QTextDocument *document)
    {
        head = new QGraphicsPixmapItem(h.scaled(QSize(48,48),Qt::KeepAspectRatio,Qt::SmoothTransformation));
        head->setData(AbstractMessageItem::Type,"head");
        head->setData(AbstractMessageItem::Name,name);
        head->setData(AbstractMessageItem::Description,desc);
        head->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
        head->setCursor(Qt::PointingHandCursor);

        msg = new QGraphicsMessageItem;
        msg->setData(AbstractMessageItem::Type,"msg");

        msg->setTextInteractionFlags(Qt::TextSelectableByMouse);
        msg->setDocument(document->clone());
    }

    QMarginsF hm;
    QMarginsF mm;
    QGraphicsPixmapItem *head;
    QGraphicsTextItem *msg;
    Qt::LayoutDirection ld;
};

MessageTextItem::MessageTextItem(const QPixmap &h, const QString &name, const QString &desc, const QList<QVariant> &msgs)
    :AbstractMessageItem(MessageType)
    ,p_d(new MessageTextItemPrivate)
{
    p_d->init(h,name,desc,msgs);
    setDirection(p_d->ld);
}

MessageTextItem::MessageTextItem(const QPixmap &h, const QString &name, const QString &desc, QTextDocument *document)
    :AbstractMessageItem(MessageType)
    ,p_d(new MessageTextItemPrivate)
{
    p_d->init(h,name,desc,document);
    setDirection(p_d->ld);
}

MessageTextItem::~MessageTextItem()
{
    delete p_d;
}

void MessageTextItem::setPos(const QPointF &pos)
{
    switch(p_d->ld)
    {
    case Qt::LeftToRight:
        p_d->head->setPos(QPointF(p_d->hm.left()+pos.x(),p_d->hm.top()+pos.y()));
        p_d->msg->setPos(QPointF(pos.x()+p_d->head->boundingRect().width()+\
                                 p_d->hm.left()+p_d->hm.right()+p_d->mm.left(),\
                                 pos.y()+p_d->mm.top()));
        break;
    case Qt::RightToLeft:
        p_d->msg->setPos(QPointF(pos.x()+p_d->mm.left(),pos.y()+p_d->mm.top()));
        p_d->head->setPos(QPointF(p_d->mm.left()+p_d->mm.right()+p_d->msg->boundingRect().width()+\
                                  pos.x()+p_d->hm.left(),p_d->hm.top()+pos.y()));
        break;
    default:
        break;
    }
    p_d->head->update();
    p_d->msg->update();
}

QPointF MessageTextItem::pos() const
{
    return p_d->head->pos();
}

QRectF MessageTextItem::boundingRect()
{
    QRectF r;
    QRectF hr = p_d->head->boundingRect();
    QRectF mr = p_d->msg->boundingRect();
    r.setTopLeft(hr.topLeft());
    qreal h1 = mr.height()+p_d->mm.top()+p_d->mm.bottom();
    qreal h2 = hr.height()+p_d->hm.top()+p_d->hm.bottom();
    r.setWidth(hr.width()+mr.width()+p_d->hm.left()+\
               p_d->hm.right()+p_d->mm.left()+p_d->mm.right());
    if(h1>h2)
        r.setHeight(h1);
    else
        r.setHeight(h2);

    return r;
}

void MessageTextItem::setView(QGraphicsView *view)
{
    if(view && view->scene())
        setScene(view->scene());
}

void MessageTextItem::setScene(QGraphicsScene *scene)
{
    if(scene)
    {
        scene->addItem(p_d->head);
        scene->addItem(p_d->msg);
    }
}

void MessageTextItem::setItemWidth(int width)
{
    QTextLayout *l = p_d->msg->document()->begin().layout();
    int count = l->lineCount();
    qreal w= p_d->msg->textWidth();
    p_d->msg->setTextWidth(width-p_d->head->boundingRect().width());

    if(l->lineCount()==count && count==1)
        p_d->msg->setTextWidth(w);
}

void MessageTextItem::setHeadMargin(const QMarginsF &m)
{
    p_d->hm = m;
    p_d->msg->update();
    p_d->head->update();
}

QMarginsF MessageTextItem::headMargin() const
{
    return p_d->hm;
}

void MessageTextItem::setMsgMargin(const QMarginsF &m)
{
    p_d->mm = m;
    p_d->msg->update();
    p_d->head->update();
}

QMarginsF MessageTextItem::msgMargin() const
{
    return p_d->mm;
}

void MessageTextItem::setDirection(Qt::LayoutDirection direction)
{
    p_d->ld = direction;
    QTextOption option(p_d->msg->document()->defaultTextOption());
    switch(direction)
    {
    case Qt::LeftToRight:
        option.setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        p_d->msg->document()->setDefaultTextOption(option);
        break;
    case Qt::RightToLeft:
        option.setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        p_d->msg->document()->setDefaultTextOption(option);
        break;
    default:
        break;
    }
}

Qt::LayoutDirection MessageTextItem::direction() const
{
    return p_d->ld;
}

class MessageVideoItemPrivate
{
public:
    MessageVideoItemPrivate()
        :ld(Qt::LeftToRight)
    {}

    void init(const QPixmap &h,const QString &name,const QString &desc,const QString &videoPath)
    {
        head = new QGraphicsPixmapItem(h);
        head->setData(AbstractMessageItem::Type,"head");
        head->setData(AbstractMessageItem::Name,name);
        head->setData(AbstractMessageItem::Description,desc);
        head->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
        head->setCursor(Qt::PointingHandCursor);

        video = new QGraphicsVideoItem;
        player.setVideoOutput(video);
        player.setMedia(QUrl(videoPath));
    }

    Qt::LayoutDirection ld;
    QMarginsF hm;
    QMarginsF vm;
    QGraphicsPixmapItem *head;
    QGraphicsVideoItem *video;
    VideoPlayer player;
};


MessageVideoItem::MessageVideoItem(const QPixmap &h,const QString &name,const QString &desc,const QString &videoPath)
    :AbstractMessageItem(MoreType)
    ,p_d(new MessageVideoItemPrivate)
{
    p_d->init(h,name,desc,videoPath);
}

MessageVideoItem::~MessageVideoItem()
{
    delete p_d;
}

void MessageVideoItem::setPos(const QPointF &pos)
{
    switch(p_d->ld)
    {
    case Qt::LeftToRight:
        p_d->head->setPos(QPointF(p_d->hm.left()+pos.x(),p_d->hm.top()+pos.y()));
        p_d->video->setPos(QPointF(pos.x()+p_d->head->boundingRect().width()+p_d->hm.left()+\
                                   p_d->hm.right()+p_d->vm.left(),pos.y()+p_d->vm.top()));
        break;
    case Qt::RightToLeft:
        p_d->video->setPos(QPointF(pos.x()+p_d->vm.left(),pos.y()+p_d->vm.top()));
        p_d->head->setPos(QPointF(p_d->vm.left()+p_d->vm.right()+p_d->video->boundingRect().width()+\
                                  pos.x()+p_d->hm.left(),p_d->hm.top()+pos.y()));
        break;
    default:
        break;
    }
}

QPointF MessageVideoItem::pos() const
{
    return p_d->head->pos();
}

QRectF MessageVideoItem::boundingRect()
{
    QRectF r;
    QRectF hr = p_d->head->boundingRect();
    QRectF vr = p_d->video->boundingRect();
    r.setTopLeft(hr.topLeft());
    r.setWidth(hr.width()+vr.width()+p_d->hm.left()+\
               p_d->hm.right()+p_d->vm.left()+p_d->vm.right());
    qreal h1 = vr.height()+p_d->vm.top()+p_d->vm.bottom();
    qreal h2 = hr.height()+p_d->hm.top()+p_d->hm.bottom();
    if(h1>h2)
        r.setHeight(h1);
    else
        r.setHeight(h2);
    return r;
}

void MessageVideoItem::setView(QGraphicsView *view)
{
    if(view && view->scene())
        setScene(view->scene());
}

void MessageVideoItem::setScene(QGraphicsScene *scene)
{
    if(scene)
    {
        scene->addItem(p_d->head);
        scene->addItem(p_d->video);
    }
}

void MessageVideoItem::setItemWidth(int width)
{
    Q_UNUSED(width)
}

QString MessageVideoItem::videoPath() const
{
    return p_d->player.media().canonicalUrl().toString();
}

void MessageVideoItem::setHeadMargin(const QMarginsF &m)
{
    p_d->hm = m;
}

QMarginsF MessageVideoItem::headMargin() const
{
    return p_d->hm;
}

void MessageVideoItem::setVideoMargin(const QMarginsF &m)
{
    p_d->vm = m;
}

QMarginsF MessageVideoItem::videoMargin() const
{
    return p_d->vm;
}

void MessageVideoItem::setDirection(Qt::LayoutDirection direction)
{
    p_d->ld = direction;
}

Qt::LayoutDirection MessageVideoItem::direction() const
{
    return p_d->ld;
}


class MessageAudioItemPrivate
{
public:
    MessageAudioItemPrivate()
        :ld(Qt::LeftToRight)
    {}

    void init(const QPixmap &h, const QString &name, const QString &audioPath, const QString &gif)
    {
        head = new QGraphicsPixmapItem(h);
        head->setData(AbstractMessageItem::Type,"head");
        head->setData(AbstractMessageItem::Name,name);

        audio = new QGraphicsAudioItem(gif);
        player.setMedia(QUrl(audioPath));
        QObject::connect(&player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),audio,SLOT(updateState(QMediaPlayer::MediaStatus)));
    }
    QGraphicsPixmapItem *head;
    QGraphicsAudioItem *audio;
    QMediaPlayer player;
    Qt::LayoutDirection ld;
    QMarginsF hm;
    QMarginsF am;
};

MessageAudioItem::MessageAudioItem(const QPixmap &h, const QString &name, const QString &voice, const QString &gif)
    :AbstractMessageItem(AudioType)
    ,p_d(new MessageAudioItemPrivate)
{
    p_d->init(h,name,voice,gif);
}

MessageAudioItem::~MessageAudioItem()
{
    delete p_d;
}

void MessageAudioItem::setPos(const QPointF &pos)
{
    switch(p_d->ld)
    {
    case Qt::LeftToRight:
        p_d->head->setPos(QPointF(p_d->hm.left()+pos.x(),p_d->hm.top()+pos.y()));
        p_d->audio->setPos(QPointF(pos.x()+p_d->head->boundingRect().width()+\
                                   p_d->hm.left()+p_d->hm.right()+p_d->am.left(),\
                                   pos.y()+p_d->am.top()));
        break;
    case Qt::RightToLeft:
        p_d->audio->setPos(QPointF(pos.x()+p_d->am.left(),pos.y()+p_d->am.top()));
        p_d->head->setPos(QPointF(p_d->am.left()+p_d->am.right()+p_d->audio->boundingRect().width()+\
                                  pos.x()+p_d->hm.left(),p_d->hm.top()+pos.y()));
        break;
    default:
        break;
    }
}

QPointF MessageAudioItem::pos() const
{
    return p_d->head->pos();
}

QRectF MessageAudioItem::boundingRect()
{
    QRectF r;
    QRectF hr = p_d->head->boundingRect();
    QRectF ar = p_d->audio->boundingRect();
    r.setTopLeft(hr.topLeft());
    r.setWidth(hr.width()+ar.width()+p_d->hm.left()+\
               p_d->hm.right()+p_d->am.left()+p_d->am.right());
    qreal h1 = ar.height()+p_d->am.top()+p_d->am.bottom();
    qreal h2 = hr.height()+p_d->hm.top()+p_d->hm.bottom();
    if(h1>h2)
        r.setHeight(h1);
    else
        r.setHeight(h2);
    return r;
}

void MessageAudioItem::setView(QGraphicsView *view)
{
    if(view && view->scene())
        setScene(view->scene());
}

void MessageAudioItem::setScene(QGraphicsScene *scene)
{
    if(scene)
    {
        scene->addItem(p_d->head);
        scene->addItem(p_d->audio);
    }
}

void MessageAudioItem::setItemWidth(int width)
{
    Q_UNUSED(width)
}

QString MessageAudioItem::audioPath() const
{
    return p_d->player.media().canonicalUrl().toString();
}

void MessageAudioItem::setDirection(Qt::LayoutDirection direction)
{
    p_d->ld = direction;
}

Qt::LayoutDirection MessageAudioItem::direction() const
{
    return p_d->ld;
}

void MessageAudioItem::setHeadMargin(const QMarginsF &m)
{
    p_d->hm = m;
}

QMarginsF MessageAudioItem::headMargin() const
{
    return p_d->hm;
}

void MessageAudioItem::setAudioMargin(const QMarginsF &m)
{
    p_d->am = m;
}

QMarginsF MessageAudioItem::audioMargin() const
{
    return p_d->am;
}

class MessageChatterItemPrivate
{
public:
    MessageChatterItemPrivate()
        :m(5.0,1.0,1.0,5.0)
    {}

    void init()
    {
        icon = new QGraphicsPixmapItem;
        icon->setPixmap(QPixmap(":/res/talk/owo.png").scaled(QSize(16,16)));
        buddy = new QGraphicsTextItem;
        buddy->setData(AbstractMessageItem::Type,"buddy");
        buddy->setTextInteractionFlags(Qt::NoTextInteraction);

        QTextCursor cursor = buddy->textCursor();
        cursor.insertText("Today Chatter:");

        contents = new QGraphicsTextItem;
        contents->setCursor(Qt::PointingHandCursor);
    }

    void init(const QString &chatter)
    {
        icon = new QGraphicsPixmapItem;
        icon->setPixmap(QPixmap(":/res/talk/owo.png").scaled(QSize(16,16)));
        buddy = new QGraphicsTextItem;
        buddy->setData(AbstractMessageItem::Type,"buddy");
        buddy->setTextInteractionFlags(Qt::NoTextInteraction);

        QTextCursor cursor = buddy->textCursor();
        cursor.insertText("Today Chatter:");

        contents = new QGraphicsTextItem;
        cursor = contents->textCursor();
        contents->setCursor(Qt::PointingHandCursor);
        cursor.insertText(chatter);
    }

    QGraphicsPixmapItem *icon;
    QGraphicsTextItem *buddy;
    QGraphicsTextItem *contents;
    QMarginsF m;
};

MessageChatterItem::MessageChatterItem()
    :AbstractMessageItem(PhotosType)
    ,p_d(new MessageChatterItemPrivate)
{
    p_d->init();
}


MessageChatterItem::MessageChatterItem(const QString &chatter)
    :AbstractMessageItem(ChatterType)
    ,p_d(new MessageChatterItemPrivate)
{
    p_d->init(chatter);
}

MessageChatterItem::~MessageChatterItem()
{
    delete p_d;
}

void MessageChatterItem::setPos(const QPointF &pos)
{
    int w = p_d->m.left()+pos.x();
    p_d->icon->setPos(QPointF(w,p_d->m.top()+pos.y()));
    w += p_d->icon->boundingRect().width();
    p_d->buddy->setPos(QPointF(w,p_d->m.top()+pos.y()));
    w += p_d->buddy->boundingRect().width();
    p_d->contents->setPos(QPointF(w,pos.y()+p_d->m.top()));
}

QPointF MessageChatterItem::pos() const
{
    return p_d->icon->pos();
}

QRectF MessageChatterItem::boundingRect()
{
    QRectF r;
    QRectF ir = p_d->icon->boundingRect();
    QRectF br = p_d->buddy->boundingRect();
    QRectF cr = p_d->contents->boundingRect();
    r.setTopLeft(ir.topLeft());
    r.setSize(QSizeF(ir.width()+br.width()+cr.width()+\
                     p_d->m.left()+p_d->m.right(),cr.height()));
    return r;
}

void MessageChatterItem::setView(QGraphicsView *view)
{
    if(view && view->scene())
        setScene(view->scene());
}

void MessageChatterItem::setScene(QGraphicsScene *scene)
{
    if(scene)
    {
        scene->addItem(p_d->icon);
        scene->addItem(p_d->buddy);
        scene->addItem(p_d->contents);
    }
}

void MessageChatterItem::setItemWidth(int width)
{
    Q_UNUSED(width)
}

bool MessageChatterItem::isEmpty() const
{
    return p_d->contents->toPlainText().isEmpty();
}

void MessageChatterItem::setChatter(const QString &chatter)
{
    p_d->contents->document()->clear();
    QTextCursor cursor = p_d->contents->textCursor();
    cursor.insertText(chatter);
}

QString MessageChatterItem::chatter() const
{
    return p_d->contents->toPlainText();
}

void MessageChatterItem::setMargin(const QMarginsF &margin)
{
    p_d->m = margin;
}

QMarginsF MessageChatterItem::margin() const
{
    return p_d->m;
}

void MessageChatterItem::setVisible(bool visible)
{
    p_d->buddy->setVisible(visible);
    p_d->contents->setVisible(visible);
    p_d->icon->setVisible(visible);
}

bool MessageChatterItem::visible() const
{
    return p_d->buddy->isVisible();
}



class MessagePhotosItemPrivate
{
public:
    MessagePhotosItemPrivate()
        :spacing(2)
        ,maxCount(4)
    {}

    void init()
    {
        buddy = new QGraphicsPixmapItem(QPixmap(":/res/talk/owp.png").scaled(QSize(12,12)));
        buddy->setData(AbstractMessageItem::Type,"buddy");

        for(int i=0;i<maxCount;i++)
        {
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem;
            item->setCursor(Qt::PointingHandCursor);
            items.append(item);
        }
    }

    void init(const QList<QPixmap> &photos)
    {
        buddy = new QGraphicsPixmapItem(QPixmap(":/res/talk/owp.png").scaled(QSize(12,12)));
        buddy->setData(AbstractMessageItem::Type,"buddy");

        for(int i=0;i<maxCount;i++)
        {
            QGraphicsPixmapItem *item;
            if(photos.count()>=(i+1) && !photos.at(i).isNull())
                item = new QGraphicsPixmapItem(photos.at(i));
            else
                item = new QGraphicsPixmapItem;
            item->setCursor(Qt::PointingHandCursor);
            items.append(item);
        }
    }
    QGraphicsPixmapItem *buddy;
    QList<QGraphicsPixmapItem *> items;
    QMarginsF m;
    qreal spacing;
    int maxCount;
};

MessagePhotosItem::MessagePhotosItem()
    :AbstractMessageItem(PhotosType)
    ,p_d(new MessagePhotosItemPrivate)
{
    p_d->init();
}

MessagePhotosItem::MessagePhotosItem(const QList<QPixmap> &photos)
    :AbstractMessageItem(PhotosType)
    ,p_d(new MessagePhotosItemPrivate)
{
    p_d->init(photos);
}

MessagePhotosItem::~MessagePhotosItem()
{
    delete p_d;
}

void MessagePhotosItem::setPos(const QPointF &pos)
{
    p_d->buddy->setPos(QPointF(p_d->m.left()+pos.x(),p_d->m.top()+pos.y()));
    qreal width = 0;
    foreach(QGraphicsPixmapItem *item,p_d->items)
    {
        item->setPos(QPointF(pos.x()+width+p_d->buddy->boundingRect().width()+\
                             p_d->m.left(),pos.y()+p_d->m.top()));
        width +=item->boundingRect().width();
    }
}

QPointF MessagePhotosItem::pos() const
{
    return p_d->buddy->pos();
}

QRectF MessagePhotosItem::boundingRect()
{
    QRectF r;
    QRectF br = p_d->buddy->boundingRect();
    r.setTopLeft(br.topLeft());
    qreal w = br.width()+p_d->m.left()+p_d->m.right();
    qreal h = br.height();
    foreach(QGraphicsPixmapItem *item,p_d->items)
    {
        QRectF cr = item->boundingRect();
        w += cr.width() + p_d->spacing;
        if(h<cr.height())
            h = cr.height();
    }
    r.setSize(QSizeF(w,h));
    return r;
}

void MessagePhotosItem::setView(QGraphicsView *view)
{
    if(view && view->scene())
        setScene(view->scene());
}

void MessagePhotosItem::setScene(QGraphicsScene *scene)
{
    if(scene)
    {
        scene->addItem(p_d->buddy);
        foreach(QGraphicsPixmapItem *item,p_d->items)
            scene->addItem(item);
    }
}

void MessagePhotosItem::setItemWidth(int width)
{
    Q_UNUSED(width)
}

bool MessagePhotosItem::isEmpty() const
{
    foreach(QGraphicsPixmapItem *item,p_d->items)
    {
        if(!item->pixmap().isNull())
            return false;
    }

    return true;
}

QList<QPixmap> MessagePhotosItem::photos() const
{
    QList<QPixmap> list;
    foreach(QGraphicsPixmapItem *item,p_d->items)
        list.append(item->pixmap());

    return list;
}

void MessagePhotosItem::setPhotos(const QList<QPixmap> &photos)
{
    int i=0;
    foreach(QGraphicsPixmapItem *item,p_d->items)
    {
        if(photos.count()<(i+1))
            break;

        item->setPixmap(photos.at(i).scaled(QSize(64,64)));
        i++;
    }
}

void MessagePhotosItem::setMargin(const QMarginsF &margin)
{
    p_d->m = margin;
}

QMarginsF MessagePhotosItem::margin() const
{
    return p_d->m;
}

qreal MessagePhotosItem::spacing() const
{
    return p_d->spacing;
}

void MessagePhotosItem::setSpacing(qreal spacing)
{
    p_d->spacing = spacing;
}

int MessagePhotosItem::maxCount() const
{
    return p_d->maxCount;
}

void MessagePhotosItem::setMaxCount(int count)
{
    p_d->maxCount = count;
    if(p_d->items.count()<=count)
    {
        for(int i=0;i<(count-p_d->items.count());i++)
            p_d->items.append(new QGraphicsPixmapItem);
    }
}

void MessagePhotosItem::setVisible(bool visible)
{
    foreach(QGraphicsPixmapItem *item,p_d->items)
        item->setVisible(visible);
}

bool MessagePhotosItem::visible() const
{
    if(!p_d->items.isEmpty())
        return p_d->items.at(0)->isVisible();
    return false;
}

MessageTimeItem::MessageTimeItem(const QString &dt)
    :AbstractMessageItem(TimeType)
{
    time = new QGraphicsTextItem(dt);

    QTextOption option(time->document()->defaultTextOption());
    option.setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    time->document()->setDefaultTextOption(option);
}

MessageTimeItem::MessageTimeItem(const QDateTime &dt)
    :AbstractMessageItem(TimeType)
{
    time = new QGraphicsTextItem(dt.toString("yyyy-mm-dd hh:mm:ss"));

    QTextOption option(time->document()->defaultTextOption());
    option.setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    time->document()->setDefaultTextOption(option);
}

MessageTimeItem::~MessageTimeItem()
{
    time->deleteLater();
}

void MessageTimeItem::setPos(const QPointF &pos)
{
    time->setPos(pos);
}

QPointF MessageTimeItem::pos() const
{
    return time->pos();
}

QRectF MessageTimeItem::boundingRect()
{
    return time->boundingRect();
}

void MessageTimeItem::setView(QGraphicsView *view)
{
    if(view && view->scene())
        setScene(view->scene());
}

void MessageTimeItem::setScene(QGraphicsScene *scene)
{
    if(scene)
        scene->addItem(time);
}

void MessageTimeItem::setItemWidth(int width)
{
    Q_UNUSED(width)
}

MessageMoreItem::MessageMoreItem()
    :AbstractMessageItem(MoreType)
{
    more = new QGraphicsTextItem;
    more->setCursor(Qt::PointingHandCursor);

    QTextOption option(more->document()->defaultTextOption());
    option.setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    more->document()->setDefaultTextOption(option);

    QTextCursor cursor = more->textCursor();
    cursor.movePosition(QTextCursor::Start);
    cursor.insertText("Check more message.");
    more->setData(Type,"more");
}

MessageMoreItem::~MessageMoreItem()
{
    more->deleteLater();
}

void MessageMoreItem::setPos(const QPointF &pos)
{
    p = pos;
}

QPointF MessageMoreItem::pos() const
{
    return more->pos();
}

QRectF MessageMoreItem::boundingRect()
{
    return more->boundingRect();
}

void MessageMoreItem::setView(QGraphicsView *view)
{
    if(view && view->scene())
        setScene(view->scene());
}

void MessageMoreItem::setScene(QGraphicsScene *scene)
{
    if(scene)
        scene->addItem(more);
}

void MessageMoreItem::setItemWidth(int width)
{
    Q_UNUSED(width)
    more->adjustSize();
    qreal x = width - more->boundingRect().width();
    more->setPos(x/2,p.y());
    more->update();
}

void MessageMoreItem::setVisible(bool visible)
{
    more->setVisible(visible);
}

bool MessageMoreItem::visible() const
{
    return more->isVisible();
}
