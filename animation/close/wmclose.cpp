#include "wmclose.h"
#include "wmclose_p.h"
#include <QPainter>
#include <QWidget>
#include <QDebug>

void WMAnimation::wm_close(QWidget *widget, WMAnimation::WMCloseType type, int msec)
{
    Q_UNUSED(widget)
    Q_UNUSED(msec)
    switch(type)
    {
    case ChildAll:
        break;
    case Single:
        break;
    default:
        qWarning() << "unknown animation type:" << type;
    }
}

class GraphicsRippleEffectPrivate
{
public:
    GraphicsRippleEffectPrivate()
        :rippleColor(Qt::white)
        ,rippleNumber(5)
        ,orientation(GraphicsRippleEffect::BottomToTop)
        ,offset(0)
        ,rippleStep(5)
        ,rippleWidth(15)
    {}

    QColor rippleColor;
    int rippleNumber;
    GraphicsRippleEffect::Orientation orientation;
    qreal offset;
    int rippleStep;
    int rippleWidth;
};

GraphicsRippleEffect::GraphicsRippleEffect(QObject *parent)
    :QGraphicsEffect(parent)
    ,p_d(new GraphicsRippleEffectPrivate)
{
}

GraphicsRippleEffect::~GraphicsRippleEffect()
{
    delete p_d;
}

void GraphicsRippleEffect::setRippleColor(const QColor &color)
{
    p_d->rippleColor = color;
    update();
}

QColor GraphicsRippleEffect::rippleColor() const
{
    return p_d->rippleColor;
}

void GraphicsRippleEffect::setRippleNumber(int num)
{
    p_d->rippleNumber = num;
    update();
}

int GraphicsRippleEffect::rippleNumber() const
{
    return p_d->rippleNumber;
}

GraphicsRippleEffect::Orientation GraphicsRippleEffect::orientation() const
{
    return p_d->orientation;
}

void GraphicsRippleEffect::setOrientation(Orientation orientation)
{
    p_d->orientation = orientation;
    update();
}

qreal GraphicsRippleEffect::offset() const
{
    return p_d->offset;
}

void GraphicsRippleEffect::setOffset(qreal offset)
{
    p_d->offset = offset;
    update();
}

int GraphicsRippleEffect::rippleStep() const
{
    return p_d->rippleStep;
}

void GraphicsRippleEffect::setRippleStep(int step)
{
    p_d->rippleStep = step;
}

int GraphicsRippleEffect::rippleWidth() const
{
    return p_d->rippleWidth;
}

void GraphicsRippleEffect::setRippleWidth(int width)
{
    p_d->rippleWidth = width;
}

void GraphicsRippleEffect::draw(QPainter *painter)
{
    if(!p_d->rippleNumber)
        return ;

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing,true);

    QPixmap pixmap = sourcePixmap();
    QPainter pter(&pixmap);

    QRectF r = boundingRect();
    qreal offset;
    qreal w;
    QLinearGradient gradient;
    switch(p_d->orientation)
    {
    case BottomToTop:
        gradient.setStart(r.left(), 0);
        gradient.setFinalStop(r.left(), r.height());

        gradient.setColorAt(0, QColor(0,0,0,0));
        offset = p_d->offset;
        w = p_d->rippleWidth;
        for(int i=0;i<p_d->rippleNumber;i++)
        {
            w = p_d->rippleWidth+i*p_d->rippleStep;
            gradient.setColorAt(offset, QColor(0,0,0,0));
            gradient.setColorAt(offset+w/2, p_d->rippleColor);
            gradient.setColorAt(offset+w, QColor(0,0,0,0));
            offset += w;
        }
        gradient.setColorAt(1.0, QColor(0,0,0,0));

        pter.setBrush(QBrush(gradient));
        pter.drawRect(r);
        break;
    case TopToBottom:
    {
        gradient.setStart(r.left(), 0);
        gradient.setFinalStop(r.left(), r.height());
        gradient.setColorAt(1.0, QColor(0,0,0,0));
        offset = p_d->offset;
        w = p_d->rippleWidth;
        for(int i=0;i<p_d->rippleNumber;i++)
        {
            w = p_d->rippleWidth+i*p_d->rippleStep;
            gradient.setColorAt(offset, QColor(0,0,0,0));
            gradient.setColorAt(offset-w/2, p_d->rippleColor);
            gradient.setColorAt(offset-w, QColor(0,0,0,0));
            offset += w;
        }
        gradient.setColorAt(0, p_d->rippleColor);

        pter.setBrush(QBrush(gradient));
        pter.drawRect(r);
        break;
    }
    case RightToLeft:
        gradient.setStart(r.left(), 0);
        gradient.setFinalStop(r.right(), 0);
        gradient.setColorAt(0, QColor(0,0,0,0));
        offset = p_d->offset;
        w = p_d->rippleWidth;
        for(int i=0;i<p_d->rippleNumber;i++)
        {
            w = p_d->rippleWidth+i*p_d->rippleStep;
            gradient.setColorAt(offset, QColor(0,0,0,0));
            gradient.setColorAt(offset-w/2, p_d->rippleColor);
            gradient.setColorAt(offset-w, QColor(0,0,0,0));
            offset += w;
        }
        gradient.setColorAt(0, p_d->rippleColor);

        pter.setBrush(QBrush(gradient));
        pter.drawRect(r);
        break;
    case LeftToRight:
        gradient.setStart(r.left(), 0);
        gradient.setFinalStop(r.right(), 0);
        gradient.setColorAt(0, QColor(0,0,0,0));
        offset = p_d->offset;
        w = p_d->rippleWidth;
        for(int i=0;i<p_d->rippleNumber;i++)
        {
            w = p_d->rippleWidth+i*p_d->rippleStep;
            gradient.setColorAt(offset, QColor(0,0,0,0));
            gradient.setColorAt(offset-w/2, p_d->rippleColor);
            gradient.setColorAt(offset-w, QColor(0,0,0,0));
            offset -= w;
        }
        gradient.setColorAt(0, p_d->rippleColor);

        pter.setBrush(QBrush(gradient));
        pter.drawRect(r);
        break;
    }

    painter->drawPixmap(boundingRect().toRect(),pixmap);

    painter->restore();
}
