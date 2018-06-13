#include "abstractbubble.h"

#include <QFile>
#include <QPainter>

class BubbleTilePrivate
{
public:
    BubbleTilePrivate(const QPixmap &t, const QString &n,BubbleTile::TilePosition tp,int z)
        :ref(1)
        ,tile(t)
        ,name(n)
        ,pos(tp)
        ,zv(z)
    {}

    int ref;
    QPixmap tile;
    QString name;
    BubbleTile::TilePosition pos;
    int zv;
};

BubbleTile::BubbleTile(const QPixmap &tile, const QString &name,TilePosition tp,int z)
    :p_d(new BubbleTilePrivate(tile,name,tp,z))
{

}

BubbleTile::BubbleTile(const BubbleTile &tile)
{
    p_d = tile.p_d;
    p_d->ref++;
}

BubbleTile::~BubbleTile()
{
    p_d->ref--;
    if(!p_d->ref)
        delete p_d;
}

bool BubbleTile::operator <(const BubbleTile &tile) const
{
    if(p_d->name<tile.p_d->name)
        return true;
    return false;
}

bool BubbleTile::operator >(const BubbleTile &tile) const
{
    if(p_d->name>tile.name())
        return true;
    return false;
}

BubbleTile &BubbleTile::operator =(const BubbleTile &tile)
{
    p_d->ref--;
    p_d = tile.p_d;
    p_d->ref++;
    return *this;
}

bool BubbleTile::operator ==(const BubbleTile &tile) const
{
    if(p_d->name==tile.name())
        return true;
    return false;
}

QPixmap &BubbleTile::tile() const
{
    return p_d->tile;
}

QString BubbleTile::name() const
{
    return p_d->name;
}

BubbleTile::TilePosition BubbleTile::pos() const
{
    return p_d->pos;
}

BubbleTile::BubbleTile()
{
}

int BubbleTile::z()const
{
    return p_d->zv;
}

AbstractBubble::AbstractBubble(const QPixmap &pixmap,const QString &n)
    :base(pixmap)
    ,name(n)
{
}

AbstractBubble::~AbstractBubble()
{
}

QString AbstractBubble::bubbleName() const
{
    return name;
}

BubbleFactory *BubbleFactory::factory = 0;

void BubbleFactory::setBubblePath(const QString &p)
{
    path = p;
}

BubbleFactory *BubbleFactory::instance()
{
    if(!factory)
        factory = new BubbleFactory;
    return factory;
}

AbstractBubble *BubbleFactory::bubble(const QString &index)
{
    if(!map.contains(index))
        return 0;

    return map[index];
}

void BubbleFactory::registerBubble(AbstractBubble *bubble)
{
    if(!bubble)
        return ;

    map[bubble->bubbleName()] = bubble;
}


