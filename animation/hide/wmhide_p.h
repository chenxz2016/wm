#ifndef WMHIDE_P_H
#define WMHIDE_P_H

#include <QObject>
#include <QPropertyAnimation>

namespace WMAnimation
{

class WMHideControl : public QObject
{
    Q_OBJECT
public:
    WMHideControl(QObject *parent = 0);
    ~WMHideControl();

    static WMHideControl *instance();

    void setFinishedProperty(QObject *obj,const char *name,const QVariant &value);

    QPropertyAnimation *animation()const;
public slots:
    void finished();
private:
    class WMHideControlPrivate *p_d;
    static WMHideControl *singlation;
};

}

#endif // WMHIDE_P_H
