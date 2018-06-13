#include "menu.h"

#include <QPainter>
#include <qssloader.h>

Menu::Menu(QWidget *parent)
    :QMenu(parent)
{
    setGraphicsEffect(new MenuGraphicEffect(this));
    setContentsMargins(8,8,8,8);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);

    setStyleSheet("QMenu::icon{background:gray}");
}

QMenu *Menu::createMenu(QWidget *parent)
{
    QMenu *menu = new QMenu(parent);
    menu->setGraphicsEffect(new MenuGraphicEffect(menu));
    menu->setContentsMargins(8,8,8,8);
    menu->setAttribute(Qt::WA_TranslucentBackground);
    menu->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);

    return menu;
}

qreal get_radius(qreal width)
{
    return width*sqrt(2.0);
}

void MenuGraphicEffect::draw(QPainter *painter)
{
    painter->save();

    QRectF r = boundingRect();
    QPixmap pixmap = sourcePixmap();

    QImage shadow(r.size().toSize(),QImage::Format_ARGB32);
    shadow.fill(Qt::transparent);

    QPainter ptr(&shadow);
    QRectF rect(r.left()+width,r.top()+width,r.width()-2*width,r.height()-2*width);
    QPainterPath path;
    path.addRoundedRect(rect,radius,radius);
    ptr.fillPath(path,Qt::transparent);

    qreal delt = radius/(width+radius);
    //Corner
    QRadialGradient lt_gradient(QPointF(width+radius,width+radius),(width+radius));
    lt_gradient.setColorAt(0,QColor(0,0,0,0));
    lt_gradient.setColorAt(delt,QColor(0,0,0,40));
    lt_gradient.setColorAt(delt+(1-delt)/2,QColor(0,0,0,15));
    lt_gradient.setColorAt(1.0,QColor(0,0,0,0));
    QBrush lt_brush(lt_gradient);
    QRect lt(0,0,width+radius,width+radius);
    ptr.fillRect(lt,lt_brush);

    QPointF lbp = r.bottomLeft();
    QRadialGradient lb_gradient(QPointF(lbp.x()+width+radius,lbp.y()-(width+radius)),(width+radius));
    lb_gradient.setColorAt(0,QColor(0,0,0,0));
    lb_gradient.setColorAt(delt,QColor(0,0,0,40));
    lb_gradient.setColorAt(delt+(1-delt)/2,QColor(0,0,0,15));
    lb_gradient.setColorAt(1.0,QColor(0,0,0,0));
    QBrush lb_brush(lb_gradient);
    QRect lb(lbp.x(),lbp.y()-(width+radius),width+radius,width+radius);
    ptr.fillRect(lb,lb_brush);

    QPointF rtp = r.topRight();
    QRadialGradient rt_gradient(QPointF(rtp.x()-(width+radius),rtp.y()+width+radius),(width+radius));
    rt_gradient.setColorAt(0,QColor(0,0,0,0));
    rt_gradient.setColorAt(delt,QColor(0,0,0,40));
    rt_gradient.setColorAt(delt+(1-delt)/2,QColor(0,0,0,15));
    rt_gradient.setColorAt(1.0,QColor(0,0,0,0));
    QBrush rt_brush(rt_gradient);
    QRect rt(rtp.x()-(width+radius),rtp.y(),width+radius,width+radius);
    ptr.fillRect(rt,rt_brush);

    QPointF rbp = r.bottomRight();
    QRadialGradient rb_gradient(QPointF(rbp.x()-(width+radius),rbp.y()-(width+radius)),(width+radius));
    rb_gradient.setColorAt(0,QColor(0,0,0,0));
    rb_gradient.setColorAt(delt,QColor(0,0,0,40));
    rb_gradient.setColorAt(delt+(1-delt)/2,QColor(0,0,0,15));
    rb_gradient.setColorAt(1.0,QColor(0,0,0,0));
    QBrush rb_brush(rb_gradient);
    QRect rb(rbp.x()-(width+radius),rbp.y()-(width+radius),width+radius,width+radius);
    ptr.fillRect(rb,rb_brush);

    /* Draw frame shadow. */
    QLinearGradient top_gradient(QPoint(width+radius,0),QPoint(width+radius,width));
    top_gradient.setColorAt(0,QColor(0,0,0,0));
    top_gradient.setColorAt(0.5,QColor(0,0,0,15));
    top_gradient.setColorAt(1.0,QColor(0,0,0,40));
    QBrush top_brush(top_gradient);
    QRect top(width+radius,0,r.width()-2*(width+radius),width);
    ptr.fillRect(top,top_brush);

    QLinearGradient bottom_gradient(QPoint(width+radius,r.height()-width),QPoint(width+radius,r.height()));
    bottom_gradient.setColorAt(0,QColor(0,0,0,40));
    bottom_gradient.setColorAt(0.5,QColor(0,0,0,15));
    bottom_gradient.setColorAt(1.0,QColor(0,0,0,0));
    QBrush bottom_brush(bottom_gradient);
    QRect bottom(width+radius,r.height()-width,r.width()-2*(width+radius),width);
    ptr.fillRect(bottom,bottom_brush);

    QLinearGradient left_gradient(QPoint(0,width+radius),QPoint(width,width+radius));
    left_gradient.setColorAt(0,QColor(0,0,0,0));
    left_gradient.setColorAt(0.5,QColor(0,0,0,15));
    left_gradient.setColorAt(1.0,QColor(0,0,0,45));
    QBrush left_brush(left_gradient);
    QRect left(0,width+radius,width,r.height()-2*(width+radius));
    ptr.fillRect(left,left_brush);

    QLinearGradient right_gradient(QPoint(r.width()-width,width+radius),QPoint(r.width(),(width+radius)));
    right_gradient.setColorAt(0,QColor(0,0,0,45));
    right_gradient.setColorAt(0.5,QColor(0,0,0,15));
    right_gradient.setColorAt(1.0,QColor(0,0,0,0));
    QBrush right_brush(right_gradient);
    QRect right(r.width()-width,width+radius,width,r.height()-2*(width+radius));
    ptr.fillRect(right,right_brush);
    ptr.end();
//    shadow.save("shadow.png");

    QImage dst(r.size().toSize(),QImage::Format_ARGB32);
    dst.fill(Qt::transparent);
    QPainter ptr1(&dst);
    ptr1.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
//    ptr1.fillRect(r, Qt::transparent);

//    pixmap.save("aaaa.png");
    ptr1.setClipping(true);
    ptr1.setClipPath(path);
    ptr1.drawPixmap(r.toRect(),pixmap);
    dst.save("dst.png");


    ptr1.setClipping(false);
    ptr1.drawImage(r,shadow);
//    pixmap.save("dst.png");

    ptr1.end();

    painter->fillRect(r,Qt::transparent);
    painter->drawImage(r.topLeft(),dst);
    painter->restore();
}
