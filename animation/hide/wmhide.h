#ifndef WMHIDE_H
#define WMHIDE_H

#include "wmglobal.h"

#include <QColor>
#include <QPoint>

class QWidget;

namespace WMAnimation
{

WM_EXPORT void hide_by_pos(QWidget *widget,int msec, const QPointF &start,const QPointF &end);

WM_EXPORT void hide_by_direction(QWidget *widget,Direction direction,int msec,qreal distance,const QPointF &start);

WM_EXPORT void hide_by_pos_with_color(QWidget *widget,int msec,const QPointF &start,const QPointF &end,const QColor &scolor,const QColor &ecolor);

WM_EXPORT void hide_by_direction_with_color(QWidget *widget,Direction direction,int msec,qreal distance,const QPointF &start,const QColor &scolor,const QColor &ecolor);

}

#endif // WMHIDE_H
