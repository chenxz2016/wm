#ifndef WMTURN_P_H
#define WMTURN_P_H

#include "wmglobal.h"

#include <QGraphicsEffect>
#include <QObject>
#include <QPropertyAnimation>

class WM_EXPORT GraphicsTurnEffect : public QGraphicsEffect
{
    Q_OBJECT
    Q_PROPERTY(qreal angle READ angle WRITE setAngle)
    Q_PROPERTY(WMAnimation::Direction direction READ direction WRITE setDirection)
    Q_PROPERTY(bool turnable READ turnable WRITE setTurnable)
public:
    GraphicsTurnEffect(QObject *parent = 0);
    ~GraphicsTurnEffect();

    qreal angle();
    void setAngle(qreal angle);

    WMAnimation::Direction direction()const;
    void setDirection(WMAnimation::Direction direction);

    bool turnable();
    void setTurnable(bool turnable);
protected:
    void draw(QPainter *painter);
private:
    class GraphicsTurnEffectPrivate *p_d;
};


namespace WMAnimation
{

class WMTurnControl : public QObject
{
    Q_OBJECT
public:
    WMTurnControl(QObject *parent = 0);
    ~WMTurnControl();

    static WMTurnControl *instance();

    QPropertyAnimation *animation()const;

    void setFinishedProperty(QObject *obj,const char *name,const QVariant &value);
    void saveConcernProperty(QObject *obj,const char *name,const QVariant &value,const QVariant &concern);
public slots:
    void finished();
    void updateValue(QVariant);
private:
    class WMTurnControlPrivate *p_d;
    static WMTurnControl *singlation;
};

}


#endif // WMTURN_P_H
