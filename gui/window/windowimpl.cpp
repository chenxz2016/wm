#include "windowimpl.h"

#include <QDebug>
#include <QGradientStop>
#include <QLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

#ifdef Q_OS_WIN
#include <windows.h>
#include <minwindef.h>

#include <windows.h>
#include <WinUser.h>
#include <windowsx.h>
#include <dwmapi.h>
#include <objidl.h> // Fixes error C2504: 'IUnknown' : base class undefined
#include <gdiplus.h>
#include <GdiPlusColor.h>
#pragma comment (lib,"Dwmapi.lib") // Adds missing library, fixes error LNK2019: unresolved external symbol __imp__DwmExtendFrameIntoClientArea
#pragma comment (lib,"user32.lib")
#endif

#ifdef Q_OS_UNIX
#include <QX11Info>
#include <xcb/xcb.h>
#endif

WindowImpl::WindowImpl(QWidget *parent)
    :mousePressEnable(false)
    ,w_p(parent)
    ,resizeFlag(true)
    ,borderWidth(8)
    ,bgColor(Qt::white)
    ,borderColor(Qt::white)
    ,resizeEnable(false)
    ,cursorShape(None)
{

}

WindowImpl::~WindowImpl()
{

}

void WindowImpl::init()
{

}

void WindowImpl::drawWindowEdge(QPainter *painter)
{
    if(!borderWidth)
        return ;

    if(w_p && painter)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(borderWidth, borderWidth, w_p->width()-2*borderWidth, w_p->height()-2*borderWidth);

        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->fillPath(path, QBrush(Qt::white));

        /* Draw Corner shadow. */
        QRadialGradient lt_gradient(QPointF(borderWidth,borderWidth),borderWidth);
        lt_gradient.setColorAt(0,QColor(0,0,0,40));
        lt_gradient.setColorAt(0.5,QColor(0,0,0,15));
        lt_gradient.setColorAt(1.0,QColor(0,0,0,0));
        QBrush lt_brush(lt_gradient);
        QRect lt(0,0,borderWidth,borderWidth);
        painter->fillRect(lt,lt_brush);

        QRadialGradient rt_gradient(QPointF(w_p->width()-borderWidth,borderWidth),borderWidth);
        rt_gradient.setColorAt(0,QColor(0,0,0,40));
        rt_gradient.setColorAt(0.5,QColor(0,0,0,15));
        rt_gradient.setColorAt(1.0,QColor(0,0,0,0));
        QBrush rt_brush(rt_gradient);
        QRect rt(w_p->width()-borderWidth,0,borderWidth,borderWidth);
        painter->fillRect(rt,rt_brush);

        QRadialGradient lb_gradient(QPointF(borderWidth,w_p->height()-borderWidth),borderWidth);
        lb_gradient.setColorAt(0,QColor(0,0,0,40));
        lb_gradient.setColorAt(0.5,QColor(0,0,0,15));
        lb_gradient.setColorAt(1.0,QColor(0,0,0,0));
        QBrush lb_brush(lb_gradient);
        QRect lb(0,w_p->height()-borderWidth,borderWidth,borderWidth);
        painter->fillRect(lb,lb_brush);

        QRadialGradient rb_gradient(QPointF(w_p->width()-borderWidth,w_p->height()-borderWidth),borderWidth);
        rb_gradient.setColorAt(0,QColor(0,0,0,40));
        rb_gradient.setColorAt(0.5,QColor(0,0,0,15));
        rb_gradient.setColorAt(1.0,QColor(0,0,0,0));
        QBrush rb_brush(rb_gradient);
        QRect rb(w_p->width()-borderWidth,w_p->height()-borderWidth,borderWidth,borderWidth);
        painter->fillRect(rb,rb_brush);

        /* Draw frame shadow. */
        QLinearGradient top_gradient(QPoint(borderWidth,0),QPoint(borderWidth,borderWidth));
        top_gradient.setColorAt(0,QColor(0,0,0,0));
        top_gradient.setColorAt(0.5,QColor(0,0,0,15));
        top_gradient.setColorAt(1.0,QColor(0,0,0,40));
        QBrush top_brush(top_gradient);
        QRect top(borderWidth,0,w_p->width()-2*borderWidth,borderWidth);
        painter->fillRect(top,top_brush);

        QLinearGradient bottom_gradient(QPoint(borderWidth,w_p->height()-borderWidth),QPoint(borderWidth,w_p->height()));
        bottom_gradient.setColorAt(0,QColor(0,0,0,40));
        bottom_gradient.setColorAt(0.5,QColor(0,0,0,15));
        bottom_gradient.setColorAt(1.0,QColor(0,0,0,0));
        QBrush bottom_brush(bottom_gradient);
        QRect bottom(borderWidth,w_p->height()-borderWidth,w_p->width()-2*borderWidth,borderWidth);
        painter->fillRect(bottom,bottom_brush);

        QLinearGradient left_gradient(QPoint(0,borderWidth),QPoint(borderWidth,borderWidth));
        left_gradient.setColorAt(0,QColor(0,0,0,0));
        left_gradient.setColorAt(0.5,QColor(0,0,0,15));
        left_gradient.setColorAt(1.0,QColor(0,0,0,45));
        QBrush left_brush(left_gradient);
        QRect left(0,borderWidth,borderWidth,w_p->height()-2*borderWidth);
        painter->fillRect(left,left_brush);

        QLinearGradient right_gradient(QPoint(w_p->width()-borderWidth,borderWidth),QPoint(w_p->width(),borderWidth));
        right_gradient.setColorAt(0,QColor(0,0,0,45));
        right_gradient.setColorAt(0.5,QColor(0,0,0,15));
        right_gradient.setColorAt(1.0,QColor(0,0,0,0));
        QBrush right_brush(right_gradient);
        QRect right(w_p->width()-borderWidth,borderWidth,borderWidth,w_p->height()-2*borderWidth);
        painter->fillRect(right,right_brush);
    }
}

void WindowImpl::drawBackground(QPainter *painter)
{
    Q_UNUSED(painter)
}

void WindowImpl::mouseMoveEvent(QMouseEvent *event)
{

    if(w_p && resizeEnable && mousePressEnable)
    {
        QPoint deltp = event->globalPos() - pressGlobalPoint;
        QRect rect(pressRect);
        switch(cursorShape)
        {
        case Top:
            rect.setY(pressRect.y()+deltp.y());
            rect.setHeight(pressRect.height()-deltp.y());
            break;
        case Bottom:
            if(rect.height() < w_p->minimumHeight())
                return ;
            rect.setHeight(pressRect.height()+deltp.y());
            break;
        case Left:
            rect.setX(pressRect.x()+deltp.x());
            rect.setWidth(pressRect.width()-deltp.x());
            break;
        case Right:
            rect.setWidth(pressRect.width()+deltp.x());
            break;
        case LeftTop:
            rect.setX(pressRect.x()+deltp.x());
            rect.setY(pressRect.y()+deltp.y());
            rect.setWidth(pressRect.width()-deltp.x());
            rect.setHeight(pressRect.height()-deltp.y());
            break;
        case RightTop:
            rect.setY(pressRect.y()+deltp.y());
            rect.setWidth(pressRect.width()+deltp.x());
            rect.setHeight(pressRect.height()-deltp.y());
            break;
        case LeftBottom:
            rect.setX(pressRect.x()+deltp.x());
            rect.setWidth(pressRect.width()-deltp.x());
            rect.setHeight(pressRect.height()+deltp.y());
            break;
        case RightBottom:
            rect.setWidth(pressRect.width()+deltp.x());
            rect.setHeight(pressRect.height()+deltp.y());
            break;
        case None:
            return ;
        }

        if(rect.width() <= w_p->minimumWidth())
            rect.setX(pressRect.x()+pressRect.width()-w_p->minimumWidth());

        if(rect.height() <= w_p->minimumHeight())
            rect.setY(pressRect.y()+pressRect.height()-w_p->minimumHeight());

        w_p->setGeometry(rect);
        return ;
    }

    if(w_p && resizeFlag)
    {
        if(event->x()>=0 && event->x()<=borderWidth && event->y()>=0 && event->y() <= borderWidth)
        {
            resizeEnable = true;
            cursorShape = LeftTop;
            w_p->setCursor(Qt::SizeFDiagCursor);
        }
        else if(event->x()>=borderWidth && event->x()<=(w_p->width()-borderWidth) && event->y()>=0 && event->y() <= borderWidth)
        {
            resizeEnable = true;
            cursorShape = Top;
            w_p->setCursor(Qt::SizeVerCursor);
        }
        else if(event->x()>=(w_p->width()-borderWidth) && event->x()<=w_p->width() && event->y()>=0 && event->y() <= borderWidth)
        {
            resizeEnable = true;
            cursorShape = RightTop;
            w_p->setCursor(Qt::SizeBDiagCursor);
        }
        else if(event->x()>=0 && event->x()<=borderWidth && event->y()>=borderWidth && event->y() <= (w_p->height()-borderWidth))
        {
            resizeEnable = true;
            cursorShape = Left;
            w_p->setCursor(Qt::SizeHorCursor);
        }
        else if(event->x()>(w_p->width()-borderWidth) && event->x()<=w_p->width() && event->y() <= (w_p->height()-borderWidth))
        {
            resizeEnable = true;
            cursorShape = Right;
            w_p->setCursor(Qt::SizeHorCursor);
        }
        else if(event->x()>=0 && event->x()<=borderWidth && event->y()>=(w_p->height()-borderWidth) && event->y() <= w_p->height())
        {
            resizeEnable = true;
            cursorShape = LeftBottom;
            w_p->setCursor(Qt::SizeBDiagCursor);
        }
        else if(event->x()>=borderWidth && event->x()<=(w_p->width()-borderWidth) && event->y()>=(w_p->height()-borderWidth) && event->y() <= w_p->height())
        {
            resizeEnable = true;
            cursorShape = Bottom;
            w_p->setCursor(Qt::SizeVerCursor);
        }
        else if(event->x()>=(w_p->width()-borderWidth) && event->x()<=w_p->width() && event->y()>=(w_p->height()-borderWidth) && event->y() <= w_p->height())
        {
            resizeEnable = true;
            cursorShape = RightBottom;
            w_p->setCursor(Qt::SizeFDiagCursor);
        }
        else
        {
            enterEdge = false;
            resizeEnable = false;
            cursorShape = None;
            w_p->setCursor(Qt::ArrowCursor);
        }
    }

    if (w_p && mousePressEnable && (event->buttons() && Qt::LeftButton))
    {
        w_p->move(event->globalPos() - mousePressPoint);
        event->accept();
    }
}

void WindowImpl::mousePressEvent(QMouseEvent *event)
{
    if (w_p && event->button() == Qt::LeftButton)
    {
        mousePressEnable = true;
        mousePressPoint = event->globalPos() - w_p->pos();
        pressGlobalPoint = event->globalPos();
        pressRect = w_p->geometry();
        event->accept();
    }
}

void WindowImpl::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    mousePressEnable = false;
}

void WindowImpl::mouseDoubleEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void WindowImpl::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)

#ifdef Q_OS_WIN
    MSG *msg = (MSG *)message;
    if(msg->message==WM_MOUSEMOVE && !mousePressEnable)
    {
        QMouseEvent e(QEvent::MouseMove,w_p->mapFromGlobal(QCursor::pos()),\
                      Qt::NoButton,Qt::NoButton,Qt::NoModifier);
        mouseMoveEvent(&e);
    }
#endif

#ifdef Q_OS_UNIX
    xcb_generic_event_t *e = static_cast<xcb_generic_event_t *>(message);
    switch (e->response_type & ~0x80) {
    case XCB_MOTION_NOTIFY:
    {
        break;
    }
    case XCB_BUTTON_PRESS:
    {
        break;
    }
    default:
        break;
    }
    QMouseEvent event(QEvent::MouseMove,w_p->mapFromGlobal(QCursor::pos()),\
                  Qt::NoButton,Qt::NoButton,Qt::NoModifier);
    mouseMoveEvent(&event);
#endif
}

void WindowImpl::enterEvent(QEvent *event)
{
    enterEdge = true;
    Q_UNUSED(event)
}

void WindowImpl::leaveEvent(QEvent *event)
{
    enterEdge = false;
    Q_UNUSED(event)
}

void WindowImpl::parentChangedEvent(QEvent *event)
{
    Q_UNUSED(event)
    if(!w_p)
        return ;

    if(w_p->parentWidget())
    {
        if(w_p->layout())
            w_p->layout()->setContentsMargins(0,0,0,0);
        borderWidth = 0;
        w_p->update();
    }
    else
    {
        if(w_p->layout())
            w_p->layout()->setContentsMargins(8,8,8,8);
        borderWidth = 8;
        w_p->update();
    }
}

void WindowImpl::update()
{
    if(w_p)
        w_p->update();
}

void WindowImpl::setParent(QWidget *parent)
{
    w_p = parent;
}
