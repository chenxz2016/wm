#ifndef REMOTECTRL_H
#define REMOTECTRL_H

#include "wmglobal.h"

#include <QPoint>
#include <QString>

class WM_EXPORT RemoteCtrl
{
public:
    RemoteCtrl(const QString &host);
    virtual ~RemoteCtrl();

    void setMousePos(const QPoint &pos);
    void setMousePress(Qt::MouseButton button);
    void setMouseRelease(Qt::MouseButton button);
    void setMouseWheeled(int delta);

    void setKeyboardPress(int key);
    void setKeyboardRelease(int key);
private:
    QString h;
    class RemoteCtrlPrivate *p_d;
    friend class RemoteCtrlPrivate;
};

#endif // REMOTECTRL_H
