#include "wmshow.h"

#include <QWidget>
#include <QGraphicsEffect>

#include "wmshow_p.h"

namespace WMAnimation
{

void show_by_pos(QWidget *widget,int msec, const QPointF &start,const QPointF &end)
{
    if(!widget || !msec)
        return ;

    QPropertyAnimation *an = WMShowControl::instance()->animation();
    if(an->state()==QAbstractAnimation::Running)
        return ;

    QObject::connect(an,SIGNAL(finished()),WMShowControl::instance(),SLOT(finished()));
    an->setTargetObject(widget);
    an->setPropertyName("pos");
    an->setDuration(msec);

    an->setStartValue(start);
    an->setEndValue(end);

    an->start();
    widget->show();
}

void show_by_direction(QWidget *widget,Direction direction,int msec,qreal distance,const QPointF &end)
{
    if(!widget || !msec)
        return ;

    QPropertyAnimation *an = WMShowControl::instance()->animation();
    if(an->state()==QAbstractAnimation::Running)
        return ;

    QObject::connect(an,SIGNAL(finished()),WMShowControl::instance(),SLOT(finished()));
    an->setTargetObject(widget);
    an->setPropertyName("pos");
    an->setDuration(msec);

    switch(direction)
    {
    case LeftToRight:
        an->setStartValue(QPointF(end.x()-distance,end.y()));
        break;
    case RightToLeft:
        an->setStartValue(QPointF(end.x()+distance,end.y()));
        break;
    case TopToBottom:
        an->setStartValue(QPointF(end.x(),end.y()-distance));
        break;
    case BottomToTop:
        an->setStartValue(QPointF(end.x(),end.y()+distance));
        break;
    }
    an->setEndValue(end);
    an->start();
    widget->show();
}

void show_by_pos_with_color(QWidget *widget,int msec,const QPointF &start,const QPointF &end,const QColor &scolor,const QColor &ecolor)
{
    if(!widget || !msec)
        return ;

    WMShowControl::instance()->setFinishedProperty(widget->graphicsEffect(),"color",ecolor);
    QPropertyAnimation *an = WMShowControl::instance()->animation();
    if(an->state()==QAbstractAnimation::Running)
        return ;

    QObject::connect(an,SIGNAL(finished()),WMShowControl::instance(),SLOT(finished()));
    an->setTargetObject(widget);
    an->setPropertyName("pos");
    an->setDuration(msec);

    an->setStartValue(start);
    an->setEndValue(end);
    widget->graphicsEffect()->setProperty("color",scolor);
    an->start();
    widget->show();
}

void show_by_direction_with_color(QWidget *widget,Direction direction,int msec,qreal distance,const QPointF &end,const QColor &scolor,const QColor &ecolor)
{
    if(!widget || !msec)
        return ;

    WMShowControl::instance()->setFinishedProperty(widget->graphicsEffect(),"color",ecolor);
    QPropertyAnimation *an = WMShowControl::instance()->animation();
    if(an->state()==QAbstractAnimation::Running)
        return ;

    QObject::connect(an,SIGNAL(finished()),WMShowControl::instance(),SLOT(finished()));
    an->setTargetObject(widget);
    an->setPropertyName("pos");
    an->setDuration(msec);

    switch(direction)
    {
    case LeftToRight:
        an->setStartValue(QPointF(end.x()-distance,end.y()));
        break;
    case RightToLeft:
        an->setStartValue(QPointF(end.x()+distance,end.y()));
        break;
    case TopToBottom:
        an->setStartValue(QPointF(end.x(),end.y()-distance));
        break;
    case BottomToTop:
        an->setStartValue(QPointF(end.x(),end.y()+distance));
        break;
    }
    an->setEndValue(end);
    widget->graphicsEffect()->setProperty("color",scolor);
    an->start();
    widget->show();
}



class WMShowControlPrivate
{
public:
    WMShowControlPrivate(WMShowControl *parent)
        :p(parent)
        ,animation(new QPropertyAnimation)
    {
        QObject::connect(animation,SIGNAL(finished()),parent,SLOT(finished()));
    }

    virtual ~WMShowControlPrivate()
    {
        animation->deleteLater();
    }

    WMShowControl *p;
    QPropertyAnimation *animation;
    QMap<QObject *,QVariant> map;
};

WMShowControl *WMShowControl::singlation = 0;

WMShowControl::WMShowControl(QObject *parent)
    :QObject(parent)
    ,p_d(new WMShowControlPrivate(this))
{
}

WMShowControl::~WMShowControl()
{
    delete p_d;
}

WMShowControl *WMShowControl::instance()
{
    if(!singlation)
         singlation = new WMShowControl;

    return singlation;
}

void WMShowControl::setFinishedProperty(QObject *obj, const char *name, const QVariant &value)
{
    QMap<QString,QVariant> map = p_d->map[obj].toMap();
    map[name] = value;
    p_d->map[obj] = map;
}

QPropertyAnimation *WMShowControl::animation() const
{
    return p_d->animation;
}

void WMShowControl::finished()
{
    QObject *obj = sender();
    if(p_d->map.contains(obj))
    {
        QMap<QString,QVariant> map = p_d->map[obj].toMap();
        QMap<QString,QVariant>::Iterator it = map.begin();
        for(;it!=map.end();it++)
            obj->setProperty(it.key().toStdString().c_str(),it.value());
    }
}

}
