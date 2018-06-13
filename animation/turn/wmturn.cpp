#include "wmturn.h"
#include "wmturn_p.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QStackedWidget>
#include <QDebug>

namespace WMAnimation
{

void turn_by_angle(QWidget *widget, Direction direction, int msec)
{
    Q_UNUSED(widget)
    Q_UNUSED(direction)
    Q_UNUSED(msec)
}

void turn_with_stacked(QStackedWidget *widget, Direction direction,int msec,int start,int end)
{
    if(start<0 || start>(widget->count()-1) || end <0 || end>(widget->count()-1))
        return ;

    GraphicsTurnEffect *effect = dynamic_cast<GraphicsTurnEffect *>(widget->graphicsEffect());
    if(!effect)
        return ;

    QPropertyAnimation *animation = WMTurnControl::instance()->animation();
    if(animation->state()==QAbstractAnimation::Running)
        return ;

    widget->setCurrentIndex(start);
    WMTurnControl::instance()->saveConcernProperty(widget,"currentIndex",end,90);
    effect->setDirection(direction);
    animation->setTargetObject(effect);
    animation->setPropertyName("angle");
    animation->setDuration(msec);
    animation->setStartValue(0);
    animation->setEndValue(180);
    WMTurnControl::instance()->setFinishedProperty(widget,"currentIndex",end);
    WMTurnControl::instance()->setFinishedProperty(effect,"turnable",false);
    effect->setProperty("turnable",true);
    animation->start();
}

WMTurnControl *WMTurnControl::singlation = 0;

class WMTurnControlPrivate
{
public:
    WMTurnControlPrivate(WMTurnControl *parent)
        :p(parent)
        ,animation(new QPropertyAnimation),
          concernUpdate(false)
    {
        QObject::connect(animation,SIGNAL(finished()),parent,SLOT(finished()));
        QObject::connect(animation,SIGNAL(valueChanged(QVariant)),p,SLOT(updateValue(QVariant)));
    }

    virtual ~WMTurnControlPrivate()
    {
        animation->deleteLater();
    }

    WMTurnControl *p;
    QPropertyAnimation *animation;
    QMap<QObject *,QVariant> map;

    typedef QMap<QObject *,QVariant> ConcernItem;
    QMap<QVariant,ConcernItem> concernMap;
    bool concernUpdate;
};

WMTurnControl::WMTurnControl(QObject *parent)
    :QObject(parent),
      p_d(new WMTurnControlPrivate(this))
{

}

WMTurnControl::~WMTurnControl()
{
    delete p_d;
}

WMTurnControl *WMTurnControl::instance()
{
    if(!singlation)
        singlation = new WMTurnControl;

    return singlation;
}

QPropertyAnimation *WMTurnControl::animation() const
{
    return p_d->animation;
}

void WMTurnControl::setFinishedProperty(QObject *obj, const char *name, const QVariant &value)
{
    QMap<QString,QVariant> map = p_d->map[obj].toMap();
    map[name] = value;
    p_d->map[obj] = map;
}

void WMTurnControl::saveConcernProperty(QObject *obj, const char *name, const QVariant &value,const QVariant &concern)
{
    WMTurnControlPrivate::ConcernItem item = p_d->concernMap[concern];
    QMap<QString,QVariant> map = item[obj].toMap();
    map[name] = value;
    item[obj] = map;
    p_d->concernMap[concern] = item;
}

void WMTurnControl::finished()
{
    p_d->concernUpdate = false;

    QObjectList l = p_d->map.keys();
    foreach(QObject *obj , l)
    {
        QMap<QString,QVariant> map = p_d->map[obj].toMap();
        QMap<QString,QVariant>::Iterator it = map.begin();
        for(;it!=map.end();it++)
            obj->setProperty(it.key().toStdString().c_str(),it.value());
    }
}

void WMTurnControl::updateValue(QVariant val)
{
    if(p_d->concernMap.contains(val.toInt()))
//    if(val.toInt()>=90 && !p_d->concernUpdate)
    {

//        WMTurnControlPrivate::ConcernItem item = p_d->concernMap[90];
        WMTurnControlPrivate::ConcernItem item = p_d->concernMap[val.toInt()];
        QObjectList l = item.keys();
        foreach(QObject *obj,l)
        {
            QMap<QString,QVariant> map = item[obj].toMap();
qDebug() << "value update:" << val;
            QMap<QString,QVariant>::Iterator it = map.begin();
            for(;it!=map.end();it++)
                obj->setProperty(it.key().toStdString().c_str(),it.value());
        }
        p_d->concernUpdate = true;
    }
}

}

class GraphicsTurnEffectPrivate
{
public:
    GraphicsTurnEffectPrivate(GraphicsTurnEffect *parent)
        :p(parent),
          angle(0),
          turnable(false)
    {}

    GraphicsTurnEffect *p;
    qreal angle;
    WMAnimation::Direction direction;
    bool turnable;
};

GraphicsTurnEffect::GraphicsTurnEffect(QObject *parent)
    :QGraphicsEffect(parent),
    p_d(new GraphicsTurnEffectPrivate(this))
{
}

GraphicsTurnEffect::~GraphicsTurnEffect()
{
    delete p_d;
}

qreal GraphicsTurnEffect::angle()
{
    return p_d->angle;
}

void GraphicsTurnEffect::setAngle(qreal angle)
{
    p_d->angle = angle;
    update();
}

WMAnimation::Direction GraphicsTurnEffect::direction() const
{
    return p_d->direction;
}

void GraphicsTurnEffect::setDirection(WMAnimation::Direction direction)
{
    p_d->direction = direction;
    update();
}

bool GraphicsTurnEffect::turnable()
{
    return p_d->turnable;
}

void GraphicsTurnEffect::setTurnable(bool turnable)
{
    p_d->turnable = turnable;
    update();
}

QPoint calculate_oringal(const QRectF &r,WMAnimation::Direction direction)
{
    QPoint p;
    switch(direction)
    {
    case WMAnimation::LeftToRight:
    case WMAnimation::RightToLeft:
        p = QPoint(r.width()/2,0);
    case WMAnimation::TopToBottom:
    case WMAnimation::BottomToTop:
        p = QPoint(0,r.height()/2);
    }
    return p;
}

QPoint calculate_pixmap_rect(const QRectF &r,WMAnimation::Direction direction)
{
    QPoint p;
    switch(direction)
    {
    case WMAnimation::LeftToRight:
    case WMAnimation::RightToLeft:
        p = QPoint(-r.width()/2,0);
    case WMAnimation::TopToBottom:
    case WMAnimation::BottomToTop:
        p = QPoint(0,-r.height()/2);
    }
    return p;
}

Qt::Axis calculate_axis(WMAnimation::Direction direction)
{
    Qt::Axis axis;
    switch(direction)
    {
    case WMAnimation::LeftToRight:
    case WMAnimation::RightToLeft:
        axis = Qt::YAxis;
    case WMAnimation::TopToBottom:
    case WMAnimation::BottomToTop:
        axis = Qt::XAxis;
    }
    return axis;
}

void GraphicsTurnEffect::draw(QPainter *painter)
{
    painter->save();
    QRectF r = boundingRect();
    QPixmap pixmap = sourcePixmap();
    QPixmap dst = pixmap.copy();
    if(p_d->turnable)
    {
        dst.fill(Qt::transparent);
        QPainter ptr(&dst);
        ptr.setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
        QTransform transform;
        QPoint p = calculate_oringal(r,p_d->direction);
        transform.translate(p.x(),p.y());

        if(p_d->angle>=90)
            transform.rotate(p_d->angle+180, calculate_axis(p_d->direction));
        else
            transform.rotate(p_d->angle, calculate_axis(p_d->direction));
        ptr.setTransform(transform);
        ptr.drawPixmap(calculate_pixmap_rect(r,p_d->direction),pixmap);
    }

    painter->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);
    painter->drawPixmap(r.toRect(),dst);
    painter->restore();
}
