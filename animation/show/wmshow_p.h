#ifndef WMSHOW_P_H
#define WMSHOW_P_H

#include <QObject>
#include <QPropertyAnimation>

namespace WMAnimation
{

class WMShowControl : public QObject
{
    Q_OBJECT
public:
    WMShowControl(QObject *parent = 0);
    ~WMShowControl();

    static WMShowControl *instance();

    void setFinishedProperty(QObject *obj,const char *name,const QVariant &value);

    QPropertyAnimation *animation()const;
public slots:
    void finished();
private:
    class WMShowControlPrivate *p_d;
    static WMShowControl *singlation;
};

}

#endif // WMSHOW_P_H
