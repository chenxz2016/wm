#ifndef WMCLOSE_P_H
#define WMCLOSE_P_H

#include "wmglobal.h"
#include <QGraphicsOpacityEffect>

class WM_EXPORT GraphicsRippleEffect : public QGraphicsEffect
{
    Q_OBJECT
    Q_PROPERTY(QColor rippleColor READ rippleColor WRITE setRippleColor)
    Q_PROPERTY(int rippleNumber READ rippleNumber WRITE setRippleNumber)
    Q_PROPERTY(Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(qreal offset READ offset WRITE setOffset)
    Q_PROPERTY(int rippleStep READ rippleStep WRITE setRippleStep)
    Q_PROPERTY(int rippleWidth READ rippleWidth WRITE setRippleWidth)
public:
    enum Orientation
    {
        RightToLeft,
        LeftToRight,
        TopToBottom,
        BottomToTop
    };

    GraphicsRippleEffect(QObject *parent = Q_NULLPTR);
    ~GraphicsRippleEffect();

    void setRippleColor(const QColor &color);
    QColor rippleColor()const;

    void setRippleNumber(int num);
    int rippleNumber()const;

    Orientation orientation()const;
    void setOrientation(Orientation orientation);

    qreal offset()const;
    void setOffset(qreal offset);

    int rippleStep()const;
    void setRippleStep(int step);

    int rippleWidth()const;
    void setRippleWidth(int width);
protected:
    void draw(QPainter *painter);
private:
    class GraphicsRippleEffectPrivate *p_d;
};

#endif // WMCLOSE_P_H
