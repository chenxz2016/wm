#include "polygonchange.h"

#include <QDateTime>
#include <QPainter>
#include <QSet>
#include <QTimer>
#include <QWidget>

namespace WMAnimation
{

class PolygonChangePrivate
{
public:
    PolygonChangePrivate(int bpNum, int rpNum, QWidget *p)
        :borderPointsNum(bpNum)
        ,randonPointsNum(rpNum)
        ,parent(p)
        ,fillColor(225,225,225)
        ,step(0.02)
    {
        if(p)
            bounding = p->rect();
    }

    qreal gen_step(int index)
    {
        if(index%5>4)
            return 0.05*(qrand()%10);
        return -0.05*(qrand()%10);
    }

    QSet<qreal> topPoints;
    QSet<qreal> bottomPoints;
    QSet<qreal> leftPoints;
    QSet<qreal> rightPoints;

    QList<QPointF> points;
    QWidget *parent;
    QRectF bounding;
    int borderPointsNum;
    int randonPointsNum;
    QColor fillColor;
    int timerID;
    qreal step;
};

static void init_randon_value(QSet<qreal> &values,int num,qreal min,qreal max)
{
    for(int i=0;i<num;i++)
    {
        qreal value=-1;
        while(value < 0 || value > (max-min))
            value = qrand()/(max-min) + min;
        values.insert(value);
    }
}

static void init_random_points(QList<QPointF> &points,int num,const QRectF &limit)
{
    for(int i=0;i<num;i++)
    {
        qreal x = -1;
        qreal y = -1;
        while(!limit.contains(x,y))
        {
            x = qrand()/limit.width()+limit.left();
            y = qrand()/limit.height()+limit.top();
        }
        points.append(QPointF(x,y));
    }
}

PolygonChange::PolygonChange(int borderPointsNum, int randonPointsNum, QWidget *parent)
    :QObject(parent)
    ,p_d(new PolygonChangePrivate(borderPointsNum,randonPointsNum,parent))
{
    qsrand(QTime::currentTime().second());
    init_randon_value(p_d->topPoints,p_d->borderPointsNum,p_d->bounding.left(),p_d->bounding.right());
    init_randon_value(p_d->bottomPoints,p_d->borderPointsNum,p_d->bounding.left(),p_d->bounding.right());
    init_randon_value(p_d->leftPoints,p_d->borderPointsNum,p_d->bounding.top(),p_d->bounding.bottom());
    init_randon_value(p_d->rightPoints,p_d->borderPointsNum,p_d->bounding.top(),p_d->bounding.bottom());

    init_random_points(p_d->points,p_d->randonPointsNum,p_d->bounding);

    p_d->timerID = startTimer(500);
}

PolygonChange::~PolygonChange()
{
    killTimer(p_d->timerID);
    delete p_d;
}

QRectF PolygonChange::boundingRect() const
{
    return p_d->bounding;
}

QColor PolygonChange::fillColor() const
{
    return p_d->fillColor;
}

void PolygonChange::update() const
{
    if(p_d->parent)
        p_d->parent->update();
}

void PolygonChange::start(int interval)
{
    p_d->timerID = startTimer(interval);
}

void PolygonChange::stop()
{
    killTimer(p_d->timerID);
}

void PolygonChange::timerEvent(QTimerEvent *event)
{
    update();
    QObject::timerEvent(event);
}

void PolygonChange::setBoundingRect(const QRect &r)
{
    p_d->bounding = r;
    p_d->topPoints.clear();
    p_d->bottomPoints.clear();
    p_d->leftPoints.clear();
    p_d->rightPoints.clear();
    p_d->points.clear();
    init_randon_value(p_d->topPoints,p_d->borderPointsNum,p_d->bounding.left(),p_d->bounding.right());
    init_randon_value(p_d->bottomPoints,p_d->borderPointsNum,p_d->bounding.left(),p_d->bounding.right());
    init_randon_value(p_d->leftPoints,p_d->borderPointsNum,p_d->bounding.left(),p_d->bounding.right());
    init_randon_value(p_d->rightPoints,p_d->borderPointsNum,p_d->bounding.left(),p_d->bounding.right());
    init_random_points(p_d->points,p_d->randonPointsNum,p_d->bounding);

    update();
}

void PolygonChange::setFillColor(const QColor &color)
{
    p_d->fillColor = color;
    update();
}

void PolygonChange::drawPolygonAnimation(QPainter *painter)
{
    static int flag = 0;
    qreal step=0;
    if(flag>200)
        step = p_d->step+0.1*(qrand()%10);
    else
        step = -(p_d->step+0.1*(qrand()%10));

    if(flag>400)
        flag = 0;

    flag++;

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    QSet<qreal> set;
    foreach(qreal x,p_d->topPoints)
        set.insert(x+p_d->gen_step(x));
    p_d->topPoints = set;

    set.clear();

    foreach(qreal x,p_d->bottomPoints)
        set.insert(x+p_d->gen_step(x));
    p_d->bottomPoints = set;

    set.clear();

    foreach(qreal y,p_d->leftPoints)
        set.insert(y+p_d->gen_step(y));
    p_d->leftPoints = set;

    set.clear();

    foreach(qreal y,p_d->rightPoints)
        set.insert(y+p_d->gen_step(y));
    p_d->rightPoints = set;

    set.clear();

    QList<QPointF> list;
    foreach(QPointF p,p_d->points)
        list.append(QPointF(p.x()+p_d->gen_step(p.x()),p.y()+p_d->gen_step(p.y())));
    p_d->points = list;

    QSet<qreal>::const_iterator i = p_d->topPoints.begin();
    for(;i!=p_d->topPoints.end();i++)
    {
        if((i+1)==p_d->topPoints.end())
            break;

        QPointF p1(*i,p_d->bounding.y());
        QPointF p2(*(i+1),p_d->bounding.y());

        QColor color(p_d->fillColor.red()+qrand()%20,
                     p_d->fillColor.green()+qrand()%20,
                     p_d->fillColor.blue()+qrand()%20);

        foreach(QPointF p,p_d->points)
        {
            QVector<QPointF> vector;
            vector.append(p1);
            vector.append(p2);
            vector.append(p);
            QPainterPath path;
            path.addPolygon(vector);
            painter->fillPath(path,color);
        }
    }

    painter->restore();
}


}
