#ifndef WMANIMATION_H
#define WMANIMATION_H

#include "wmglobal.h"

class QWidget;

namespace WMAnimation
{

enum WMCloseType
{
    ChildAll,
    Single
};

WM_EXPORT void wm_close(QWidget *widget,WMCloseType type,int msec);
}

#endif // WMANIMATION_H
