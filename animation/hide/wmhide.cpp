#include "wmhide.h"
#include "wmhide_p.h"

#include <QWidget>
#include <QGraphicsEffect>

namespace WMAnimation
{

void hide_by_pos(QWidget *widget,int msec, const QPointF &start,const QPointF &end)
{
    if(!widget || !msec)
        return ;

    QPropertyAnimation *an = WMHideControl::instance()->animation();
    if(an->state()==QAbstractAnimation::Running)
        return ;

    QObject::connect(an,SIGNAL(finished()),widget,SLOT(hide()));
    an->setTargetObject(widget);
    an->setPropertyName("pos");
    an->setDuration(msec);

    an->setStartValue(start);
    an->setEndValue(end);

    an->start();
}

void hide_by_direction(QWidget *widget,Direction direction,int msec,qreal distance,const QPointF &start)
{
    if(!widget || !msec)
        return ;

    QPropertyAnimation *an = WMHideControl::instance()->animation();
    if(an->state()==QAbstractAnimation::Running)
        return ;

    QObject::connect(an,SIGNAL(finished()),widget,SLOT(hide()));

    an->setTargetObject(widget);
    an->setPropertyName("pos");
    an->setDuration(msec);

    an->setStartValue(start);
    switch(direction)
    {
    case LeftToRight:
        an->setEndValue(QPointF(start.x()-distance,start.y()));
        break;
    case RightToLeft:
        an->setEndValue(QPointF(start.x()+distance,start.y()));
        break;
    case TopToBottom:
        an->setEndValue(QPointF(start.x(),start.y()-distance));
        break;
    case BottomToTop:
        an->setEndValue(QPointF(start.x(),start.y()+distance));
        break;
    }

    an->start();
}

void hide_by_pos_with_color(QWidget *widget,int msec,const QPointF &start,const QPointF &end,const QColor &scolor,const QColor &ecolor)
{
    if(!widget || !msec)
        return ;

    WMHideControl::instance()->setFinishedProperty(widget->graphicsEffect(),"color",ecolor);
    QPropertyAnimation *an = WMHideControl::instance()->animation();
    if(an->state()==QAbstractAnimation::Running)
        return ;

    QObject::connect(an,SIGNAL(finished()),widget,SLOT(hide()));
    an->setTargetObject(widget);
    an->setPropertyName("pos");
    an->setDuration(msec);

    an->setStartValue(start);
    an->setEndValue(end);
    widget->graphicsEffect()->setProperty("color",scolor);
    an->start();
}

void hide_by_direction_with_color(QWidget *widget,Direction direction,int msec,qreal distance,const QPointF &start,const QColor &scolor,const QColor &ecolor)
{
    if(!widget || !msec)
        return ;

    WMHideControl::instance()->setFinishedProperty(widget->graphicsEffect(),"color",ecolor);
    QPropertyAnimation *an = WMHideControl::instance()->animation();
    if(an->state()==QAbstractAnimation::Running)
        return ;

    QObject::connect(an,SIGNAL(finished()),widget,SLOT(hide()));
    an->setTargetObject(widget);
    an->setPropertyName("pos");
    an->setDuration(msec);

    an->setStartValue(start);
    switch(direction)
    {
    case LeftToRight:
        an->setEndValue(QPointF(start.x()-distance,start.y()));
        break;
    case RightToLeft:
        an->setEndValue(QPointF(start.x()+distance,start.y()));
        break;
    case TopToBottom:
        an->setEndValue(QPointF(start.x(),start.y()-distance));
        break;
    case BottomToTop:
        an->setEndValue(QPointF(start.x(),start.y()+distance));
        break;
    }

    widget->graphicsEffect()->setProperty("color",scolor);
    an->start();
}



class WMHideControlPrivate
{
public:
    WMHideControlPrivate(WMHideControl *parent)
        :p(parent)
        ,animation(new QPropertyAnimation)
    {
        QObject::connect(animation,SIGNAL(finished()),parent,SLOT(finished()));
    }

    virtual ~WMHideControlPrivate()
    {
        animation->deleteLater();
    }

    WMHideControl *p;
    QPropertyAnimation *animation;
    QMap<QObject *,QVariant> map;
};

WMHideControl *WMHideControl::singlation = 0;

WMHideControl::WMHideControl(QObject *parent)
    :QObject(parent)
    ,p_d(new WMHideControlPrivate(this))
{
}

WMHideControl::~WMHideControl()
{
    delete p_d;
}

WMHideControl *WMHideControl::instance()
{
    if(!singlation)
         singlation = new WMHideControl;

    return singlation;
}

void WMHideControl::setFinishedProperty(QObject *obj, const char *name, const QVariant &value)
{
    QMap<QString,QVariant> map = p_d->map[obj].toMap();
    map[name] = value;
    p_d->map[obj] = map;
}

QPropertyAnimation *WMHideControl::animation() const
{
    return p_d->animation;
}

void WMHideControl::finished()
{
    QObject *obj = sender();
    if(p_d->map.contains(obj))
    {
        QMap<QString,QVariant> map = p_d->map[obj].toMap();
        QMap<QString,QVariant>::Iterator it = map.begin();
        for(;it!=map.end();it++)
            obj->setProperty(it.key().toStdString().c_str(),it.value());
        obj->setProperty("visible",false);
    }
}

}
