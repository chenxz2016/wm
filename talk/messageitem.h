#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H

#include <QGraphicsTextItem>
#include <QWidget>

#include <QtMultimedia/QMediaPlayer>

#include <video/videoplayer.h>

class QMouseEvent;
class QPainter;
class MessageView;

class QGraphicsView;
class QGraphicsScene;

class QGraphicsMessageItem : public QGraphicsTextItem
{
    Q_OBJECT
    Q_PROPERTY(qreal margin READ margin WRITE setMargin)
public:
    QGraphicsMessageItem(QGraphicsItem *parent = 0);
    QGraphicsMessageItem(const QString &text, QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    qreal margin()const;
    void setMargin(const qreal &m);
protected:
    void drawDecoration(QPainter *painter);
private:
    QString bubble;
};


enum ItemType
{
    AbstractType = 0,
    MessageType,
    VideoType,
    AudioType,
    ChatterType,
    PhotosType,
    TimeType,
    MoreType
};

class AbstractMessageItem
{
public:
    AbstractMessageItem(int type):t(type){}
    virtual ~AbstractMessageItem(){}

    int type()const{return t;}

    virtual void setPos(const QPointF &pos)=0;
    virtual QPointF pos()const=0;
    virtual QRectF boundingRect() = 0;
    virtual void setView(QGraphicsView *view) = 0;
    virtual void setScene(QGraphicsScene *scene) = 0;
    virtual void setItemWidth(int width) = 0;

    void setData(const QVariant &d,int flag){map[flag] = d;}
    QVariant data(int flag)const{return map[flag];}

    enum ItemDataType
    {
        Name,
        Type,
        Description
    };
private:
    int t;
    QMap<int,QVariant> map;
};

class QGraphicsPixmapItem;

class MessageTextItem : public AbstractMessageItem
{
public:
    MessageTextItem(const QPixmap &h,const QString &name,const QString &desc,const QList<QVariant> &msgs);
    MessageTextItem(const QPixmap &h,const QString &name,const QString &desc,QTextDocument *document);
    ~MessageTextItem();

    void setPos(const QPointF &pos);
    QPointF pos()const;

    QRectF boundingRect();

    void setView(QGraphicsView *view);
    void setScene(QGraphicsScene *scene);

    void setItemWidth(int width);

    void setHeadMargin(const QMarginsF &m);
    QMarginsF headMargin()const;

    void setMsgMargin(const QMarginsF &m);
    QMarginsF msgMargin()const;

    void setDirection(Qt::LayoutDirection direction);
    Qt::LayoutDirection direction()const;
private:
    class MessageTextItemPrivate *p_d;
};

class QGraphicsVideoItem;

class MessageVideoItem : public AbstractMessageItem
{
public:
    MessageVideoItem(const QPixmap &h,const QString &name,const QString &desc,const QString &videoPath);
    ~MessageVideoItem();

    void setPos(const QPointF &pos);
    QPointF pos()const;

    QRectF boundingRect();

    void setView(QGraphicsView *view);
    void setScene(QGraphicsScene *scene);

    void setItemWidth(int width);

    QString videoPath()const;

    void setHeadMargin(const QMarginsF &m);
    QMarginsF headMargin()const;

    void setVideoMargin(const QMarginsF &m);
    QMarginsF videoMargin()const;

    void setDirection(Qt::LayoutDirection direction);
    Qt::LayoutDirection direction()const;

private:
    class MessageVideoItemPrivate *p_d;
};

class QGraphicsAudioItem;
class MessageAudioItem : public AbstractMessageItem
{
public:
    MessageAudioItem(const QPixmap &h,const QString &name,const QString &voice,const QString &gif);
    ~MessageAudioItem();

    void setPos(const QPointF &pos);
    QPointF pos()const;

    QRectF boundingRect();

    void setView(QGraphicsView *view);
    void setScene(QGraphicsScene *scene);

    void setItemWidth(int width);

    QString audioPath()const;

    void setDirection(Qt::LayoutDirection direction);
    Qt::LayoutDirection direction()const;

    void setHeadMargin(const QMarginsF &m);
    QMarginsF headMargin()const;

    void setAudioMargin(const QMarginsF &m);
    QMarginsF audioMargin()const;
private:
    class MessageAudioItemPrivate *p_d;

};

class MessageChatterItem : public AbstractMessageItem
{
    friend class ContactTalkPrivate;
    friend class ContactTalk;
    friend class MultiTalkPrivate;
    friend class MultiTalk;
    friend class GroupTalkPrivate;
    friend class GroupTalk;
protected:
    MessageChatterItem();
public:
    MessageChatterItem(const QString &chatter);
    ~MessageChatterItem();

    void setPos(const QPointF &pos);
    QPointF pos()const;

    QRectF boundingRect();

    void setView(QGraphicsView *view);
    void setScene(QGraphicsScene *scene);

    void setItemWidth(int width);

    bool isEmpty()const;

    void setChatter(const QString &chatter);
    QString chatter()const;

    void setMargin(const QMarginsF &margin);
    QMarginsF margin()const;

    void setVisible(bool visible);
    bool visible()const;
private:
    class MessageChatterItemPrivate *p_d;
};

class MessagePhotosItem : public AbstractMessageItem
{
    friend class ContactTalkPrivate;
    friend class ContactTalk;
    friend class MultiTalkPrivate;
    friend class MultiTalk;
    friend class GroupTalkPrivate;
    friend class GroupTalk;
protected:
    MessagePhotosItem();
public:
    MessagePhotosItem(const QList<QPixmap> &photos);
    ~MessagePhotosItem();

    void setPos(const QPointF &pos);
    QPointF pos()const;

    QRectF boundingRect();

    void setView(QGraphicsView *view);
    void setScene(QGraphicsScene *scene);

    void setItemWidth(int width);

    bool isEmpty()const;

    QList<QPixmap> photos()const;
    void setPhotos(const QList<QPixmap> &photos);

    void setMargin(const QMarginsF &margin);
    QMarginsF margin()const;

    qreal spacing()const;
    void setSpacing(qreal spacing);

    int maxCount()const;
    void setMaxCount(int count);

    void setVisible(bool visible);
    bool visible()const;
private:
    class MessagePhotosItemPrivate *p_d;

};

class MessageTimeItem : public AbstractMessageItem
{
public:
    MessageTimeItem(const QString &dt);
    MessageTimeItem(const QDateTime &dt);
    ~MessageTimeItem();

    void setPos(const QPointF &pos);
    QPointF pos()const;

    QRectF boundingRect();

    void setView(QGraphicsView *view);
    void setScene(QGraphicsScene *scene);

    void setItemWidth(int width);
private:
    QGraphicsTextItem *time;
};

class MessageMoreItem : public AbstractMessageItem
{
public:
    MessageMoreItem();
    ~MessageMoreItem();

    void setPos(const QPointF &pos);
    QPointF pos()const;

    QRectF boundingRect();

    void setView(QGraphicsView *view);
    void setScene(QGraphicsScene *scene);

    void setItemWidth(int width);

    void setVisible(bool visible);
    bool visible()const;
private:
    QGraphicsTextItem *more;
    QPointF p;
};

#endif // MESSAGEITEM_H
