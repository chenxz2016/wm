#ifndef WMANIMATION_H
#define WMANIMATION_H

#include "wmglobal.h"

#include <QColor>
#include <QPoint>

class QWidget;

namespace WMAnimation
{

WM_EXPORT void show_by_pos(QWidget *widget,int msec, const QPointF &start,const QPointF &end);

WM_EXPORT void show_by_direction(QWidget *widget,Direction direction,int msec,qreal distance,const QPointF &end);

WM_EXPORT void show_by_pos_with_color(QWidget *widget,int msec,const QPointF &start,const QPointF &end,const QColor &scolor,const QColor &ecolor);

WM_EXPORT void show_by_direction_with_color(QWidget *widget,Direction direction,int msec,qreal distance,const QPointF &end,const QColor &scolor,const QColor &ecolor);

}

#endif // WMANIMATION_H
