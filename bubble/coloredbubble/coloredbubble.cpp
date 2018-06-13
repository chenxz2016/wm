#include "coloredbubble.h"

#include <QFile>
#include <QPainter>

ColoredBubble::ColoredBubble(const QPixmap &pixmap,int px1,int px2,\
                             int py1,int py2,const QColor &color,const QString &n)
    :AbstractBubble(pixmap,n)
    ,bgColor(color)
{
    int x1 = px1;
    int x2 = px2;
    int y1 = py1;
    int y2 = py2;

    QRectF rect = base.rect();

    BubbleTile lt(base.copy(rect.left(),rect.top(),x1,y1),"LeftTop",BubbleTile::LeftTop,0);
    tiles.append(lt);
    BubbleTile t(base.copy(x1,rect.top(),x2-x1,y1),"Top",BubbleTile::Top,0);
    tiles.append(t);
    BubbleTile rt(base.copy(x2,rect.top(),rect.right()-x2,y1),"RightTop",BubbleTile::RightTop,0);
    tiles.append(rt);
    BubbleTile left(base.copy(rect.left(),y1,x1,y2-y1),"Left",BubbleTile::Left,0);
    tiles.append(left);
    BubbleTile c(base.copy(x1,y1,x2-x1,y2-y1),"Center",BubbleTile::Center,0);
    tiles.append(c);
    BubbleTile r(base.copy(x2,y1,rect.right()-x2,y2-y1),"Right",BubbleTile::Right,0);
    tiles.append(r);
    BubbleTile lb(base.copy(rect.left(),y2,x1,rect.bottom()-y2),"LeftBottom",BubbleTile::LeftBottom,0);
    tiles.append(lb);
    BubbleTile b(base.copy(x1,y2,x2-x1,rect.bottom()-y2),"Bottom",BubbleTile::Bottom,0);
    tiles.append(b);
    BubbleTile rb(base.copy(x2,y2,rect.right()-x2,rect.bottom()-y2),"RightBottom",BubbleTile::RightBottom,0);
    tiles.append(rb);
}

void ColoredBubble::appendTile(const BubbleTile &tile)
{
    if(tile.z()>0)
        ups.append(tile);
    else
        downs.append(tile);
}

void ColoredBubble::appendTiles(const QList<BubbleTile> &list)
{
    foreach(BubbleTile tile,list)
        appendTile(tile);
}

void ColoredBubble::removeTile(const BubbleTile &tile)
{
    ups.removeAll(tile);
    downs.removeAll(tile);
}

QPixmap ColoredBubble::merge(const QRectF &r,const QMarginsF &m)
{
    Q_UNUSED(m)
    QPixmap p(r.size().toSize());
    QPainter painter(&p);
    painter.fillRect(p.rect(),bgColor);

    drawDowns(r,&painter);
    drawBase(r,&painter);
    drawUps(r,&painter);

    return p;
}

void ColoredBubble::drawBase(const QRectF &r, QPainter *painter)
{
    painter->setPen(Qt::NoPen);
    QPointF p;
    QRectF rect;
    qreal x1,x2;
    qreal y1,y2;
    foreach(BubbleTile tile,tiles)
    {
        QSize s = tile.tile().size();
        switch(tile.pos())
        {
        case BubbleTile::LeftTop:
            p = r.topLeft();
            painter->drawPixmap(p,tile.tile());
            x1 = s.width();
            y1 = s.height();
            break;
        case BubbleTile::LeftBottom:
            p.setX(r.left());
            p.setY(r.bottom()-s.height());
            painter->drawPixmap(p,tile.tile());
            x1 = s.width();
            y2 = p.y();
            break;
        case BubbleTile::RightTop:
            p.setX(r.right()-s.width());
            p.setY(r.top());
            painter->drawPixmap(p,tile.tile());
            x2 = p.x();
            y1 = s.height();
            break;
        case BubbleTile::RightBottom:
            p.setX(r.right()-s.width());
            p.setY(r.bottom()-s.height());
            painter->drawPixmap(p,tile.tile());
            x2 = p.x();
            y2 = p.y();
            break;
        default:
            continue;
        }
    }

    foreach(BubbleTile tile,tiles)
    {
        switch(tile.pos())
        {
        case BubbleTile::Left:
            rect.setLeft(r.left());
            rect.setRight(x1);
            rect.setTop(y1);
            rect.setBottom(y2);
            painter->drawPixmap(rect,tile.tile(),QRectF(tile.tile().rect()));
            break;
        case BubbleTile::Right:
            rect.setLeft(x2);
            rect.setRight(r.right());
            rect.setTop(y1);
            rect.setBottom(y2);
            painter->drawPixmap(rect,tile.tile(),QRectF(tile.tile().rect()));
            break;
        case BubbleTile::Top:
            rect.setLeft(x1);
            rect.setRight(x2);
            rect.setTop(r.top());
            rect.setBottom(y1);
            painter->drawPixmap(rect,tile.tile(),QRectF(tile.tile().rect()));
            break;
        case BubbleTile::Bottom:
            rect.setLeft(x1);
            rect.setRight(x2);
            rect.setTop(y2);
            rect.setBottom(r.bottom());
            painter->drawPixmap(rect,tile.tile(),QRectF(tile.tile().rect()));
            break;
        case BubbleTile::Center:
            rect.setLeft(x1);
            rect.setRight(x2);
            rect.setTop(y1);
            rect.setBottom(y2);
            painter->drawPixmap(rect,tile.tile(),QRectF(tile.tile().rect()));
            break;
        default:
            continue;
        }
    }
}

void ColoredBubble::drawTils(const QList<BubbleTile> &tiles,const QRectF &r,QPainter *painter)
{
    QPointF p;
    QRect rect;
    foreach(BubbleTile tile,tiles)
    {
        QSize s = tile.tile().size();
        switch(tile.pos())
        {
        case BubbleTile::Left:
            painter->setBrush(QBrush(tile.tile()));
            rect.setLeft(r.left());
            rect.setRight(r.left()+s.width());
            rect.setTop(r.top());
            rect.setBottom(r.bottom());
            painter->drawPixmap(rect,tile.tile());
            break;
        case BubbleTile::Right:
            painter->setBrush(QBrush(tile.tile()));
            rect.setLeft(r.right()-s.width());
            rect.setRight(r.right());
            rect.setTop(r.top());
            rect.setBottom(r.bottom());
            painter->drawPixmap(rect,tile.tile());
            break;
        case BubbleTile::Top:
            painter->setBrush(QBrush(tile.tile()));
            rect.setLeft(r.left());
            rect.setRight(r.right());
            rect.setTop(r.top());
            rect.setHeight(s.height());
            painter->drawPixmap(rect,tile.tile());
            break;
        case BubbleTile::Bottom:
            painter->setPen(Qt::NoPen);
            painter->setBrush(QBrush(tile.tile()));
            rect.setLeft(r.left());
            rect.setRight(r.right());
            rect.setTop(r.bottom()-s.height());
            rect.setHeight(s.height());
            painter->drawRect(rect);
            painter->drawPixmap(rect,tile.tile());
            continue;
        case BubbleTile::LeftTop:
            p = r.topLeft();
            break;
        case BubbleTile::LeftBottom:
            p.setX(r.left());
            p.setY(r.bottom()-s.height());
            break;
        case BubbleTile::RightTop:
            p.setX(r.right()-s.width());
            p.setY(r.top());
            break;
        case BubbleTile::RightBottom:
            p.setX(r.right()-s.width());
            p.setY(r.bottom()-s.height());
            break;
        case BubbleTile::Center:
            p.setX(r.center().x()-s.width()/2.0);
            p.setY(r.center().y()-s.height()/2.0);
            break;
        default:
            continue;
        }
        painter->drawPixmap(p,tile.tile());
    }
}

void ColoredBubble::drawUps(const QRectF &r,QPainter *painter)
{
    drawTils(ups,r,painter);
}

void ColoredBubble::drawDowns(const QRectF &r, QPainter *painter)
{
    drawTils(downs,r,painter);
}

AbstractBubble *parserColoredBubble(const QString &fileName, QString &error)
{
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
    {
        error = file.errorString();
        return 0;
    }

    QByteArray data = file.readAll();

    int rnum = 0;
    int start;
    int end;

    start = data.indexOf("[@bubble]",rnum);
    if(start==-1)
    {
        error = "Bubble format start error.";
        return 0;
    }

    end = data.indexOf("[bubble@]",rnum);
    if(end==-1)
    {
        error = "Bubble format end error.";
        return 0;
    }

    QString name;
    QColor bgColor;
    int x1,x2,y1,y2;
    QByteArray head(data.mid(start+9,end));
    QPixmap bgPixmap;

    /* name */
    start = head.indexOf("[@name]");
    if(start==-1)
    {
        error = "No head start";
        return 0;
    }

    end = head.indexOf("[name@]");
    if(end==-1)
    {
        error = "No head end.";
        return 0;
    }

    if((start+7)>end)
    {
        error = "Name property error.";
        return 0;
    }

    name = QString(head.mid(start+7,end-(start+7)));

    /* background */
    start = head.indexOf("[@background]");
    if(start==-1)
    {
        error = "No background start.";
        return 0;
    }

    end = head.indexOf("[background@]");
    if(end==-1)
    {
        error = "No background end.";
        return 0;
    }

    if((start+13)>end)
    {
        error = "Background property error.";
        return 0;
    }

    bgColor = QString(head.mid(start+13,end-(start+13)));

    /* x1,x2,y1,y2 */
    start = head.indexOf("[@splitter]");
    if(start==-1)
    {
        error = "No splitter start.";
        return 0;
    }

    end = head.indexOf("[splitter@]");
    if(end==-1)
    {
        error = "No splitter end.";
        return 0;
    }

    if((start+11)>end)
    {
        error = "Splitter property error.";
        return 0;
    }

    QList<QByteArray> l = head.mid(start+11,end-(start+11)).split(',');
    if(l.count()==4)
    {
        if(l.at(0).toInt()>l.at(1).toInt())
        {
            x1 = l.at(1).toInt();
            x2 = l.at(0).toInt();
        }
        else
        {
            x2 = l.at(1).toInt();
            x1 = l.at(0).toInt();
        }
        if(l.at(2).toInt()>l.at(3).toInt())
        {
            y1 = l.at(3).toInt();
            y2 = l.at(2).toInt();
        }
        else
        {
            y2 = l.at(3).toInt();
            y1 = l.at(2).toInt();
        }
    }
    else
    {
        error = "Splitter property error.";
        return 0;
    }

    /* pixmap */
    start = head.indexOf("[@pixmap]");
    if(start==-1)
    {
        error = "No pixmap head.";
        return 0;
    }

    end = head.indexOf("[pixmap@]");
    if(end==-1)
    {
        error = "No pixmap end.";
        return 0;
    }

    bgPixmap.loadFromData(head.mid(start+9,end-(start+9)),"PNG");

    ColoredBubble *cb = new ColoredBubble(bgPixmap,x1,x2,y1,y2,bgColor,name);

    start = data.indexOf("[$tiles]");
    if(start==-1)
        return cb;

    end = data.indexOf("[tiles$]");
    if(end==-1)
        return cb;

    QByteArray tiles = data.mid(start+8,end-(start+8));
    while(1)
    {
        start = tiles.indexOf("[$tile]",rnum);
        if(start==-1)
            return cb;

        end = data.indexOf("[tile$]",rnum);
        if(end==-1)
            return cb;

        rnum = end;

        if((start+7)>end)
            return cb;

        BubbleTile::TilePosition tp;
        QString name;
        QByteArray tile = tiles.mid(start+7,end-(start+7));

        /* name */
        start = tile.indexOf("[$name]");
        if(start==-1)
            return cb;

        end = tile.indexOf("[name$]");
        if(end==-1)
            return cb;

        name = QString(tile.mid(start+7,end-(start+7)));

        /* position */
        start = tile.indexOf("[$position]");
        if(start==-1)
            return cb;

        end = tile.indexOf("[position$]");
        if(end==-1)
            return cb;

        QByteArray pos = tile.mid(start+11,end-(start+11));
        if(pos=="Left")
            tp = BubbleTile::Left;
        else if(pos=="Right")
            tp = BubbleTile::Right;
        else if(pos=="Top")
            tp = BubbleTile::Top;
        else if(pos=="Bottom")
            tp = BubbleTile::Bottom;
        else if(pos=="LeftTop")
            tp = BubbleTile::LeftTop;
        else if(pos=="LeftBottom")
            tp = BubbleTile::LeftBottom;
        else if(pos=="RightTop")
            tp = BubbleTile::RightTop;
        else if(pos=="RightBottom")
            tp = BubbleTile::RightBottom;
        else if(pos=="Center")
            tp = BubbleTile::Center;

        /* position */
        start = tile.indexOf("[$pixmap]");
        if(start==-1)
            return cb;

        end = tile.indexOf("[pixmap$]");
        if(end==-1)
            return cb;

        bgPixmap.loadFromData(tile.mid(start+9,end-(start+9)),"PNG");

        /* position */
        start = tile.indexOf("[$z]");
        if(start==-1)
            return cb;

        end = tile.indexOf("[z$]");
        if(end==-1)
            return cb;

        int z = tile.mid(start+4,end-(start+4)).toInt();
        BubbleTile t(bgPixmap,name,tp,z);
        cb->appendTile(t);
    }

    return cb;
}
