#ifndef POLYGONCHANGE_H
#define POLYGONCHANGE_H

#include "wmglobal.h"

#include <QPoint>
#include <QTimeLine>

class QWidget;
class QPainter;

namespace WMAnimation
{

class WM_EXPORT PolygonChange : public QObject
{
    Q_OBJECT
public:
    PolygonChange(int borderPointsNum,int randonPointsNum,QWidget *parent = 0);
    virtual ~PolygonChange();

    QRectF boundingRect()const;

    QColor fillColor()const;

    void update()const;

    void start(int interval);
    void stop();
protected:
    void timerEvent(QTimerEvent *event);
    void setBoundingRect(const QRect &r);
    void setFillColor(const QColor &color);

    void drawPolygonAnimation(QPainter *painter);
private:
    class PolygonChangePrivate *p_d;
    friend class LoginWindow;
    friend class LoginWindowPrivate;
};

}

#endif // POLYGONCHANGE_H
