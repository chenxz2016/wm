#ifndef ABSTRACTBUBBLE_H
#define ABSTRACTBUBBLE_H

#include <QMap>
#include <QPixmap>
#include <wmglobal.h>

class WM_EXPORT BubbleTile
{
public:
    enum TilePosition
    {
        Left,
        Right,
        Top,
        Bottom,
        LeftTop,
        LeftBottom,
        RightTop,
        RightBottom,
        Center
    };

    BubbleTile(const QPixmap &tile,const QString &name,TilePosition tp,int z);
    BubbleTile(const BubbleTile &tile);
    virtual ~BubbleTile();

    bool operator <(const BubbleTile &tile)const;
    bool operator >(const BubbleTile &tile)const;
    BubbleTile& operator = (const BubbleTile &tile);
    bool operator ==(const BubbleTile &tile)const;

    QPixmap& tile()const;
    QString name()const;
    TilePosition pos()const;
    int z()const;
protected:
    BubbleTile();
private:
    class BubbleTilePrivate *p_d;
    friend class BubbleTilePrivate;
};

class WM_EXPORT AbstractBubble
{
public:
    virtual ~AbstractBubble();

    QString bubbleName()const;
protected:
    AbstractBubble(const QPixmap &pixmap,const QString &n);

    virtual QPixmap merge(const QRectF &r,const QMarginsF &m) = 0;

    QPixmap base;
    QList<BubbleTile> ups;
    QList<BubbleTile> downs;
private:
    QString name;
    friend class QGraphicsMessageItem;
};

class WM_EXPORT BubbleFactory
{
public:
    void setBubblePath(const QString &p);
    static BubbleFactory *instance();
    virtual AbstractBubble *bubble(const QString &index);
protected:
    void registerBubble(AbstractBubble *bubble);
private:
    BubbleFactory(){}
    static BubbleFactory *factory;
    QString path;
    QMap<QString,AbstractBubble *> map;
};

#endif // ABSTRACTBUBBLE_H
