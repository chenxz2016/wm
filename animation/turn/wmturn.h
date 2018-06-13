#ifndef WMTURN_H
#define WMTURN_H

#include "wmglobal.h"


class QWidget;
class QStackedWidget;

namespace WMAnimation
{

WM_EXPORT void turn_by_angle(QWidget *widget,Direction direction,int msec);

WM_EXPORT void turn_with_stacked(QStackedWidget *widget,Direction direction, int msec,int start,int end);

}
#endif // WMTURN_H
