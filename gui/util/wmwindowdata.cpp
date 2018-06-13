#include "wmwindowdata.h"

#include <QDebug>
#include <QGradientStop>
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

WMWindowData::WMWindowData(QWidget *parent)
    :m_mousePressEnable(false)
    ,m_parent(parent)
    ,m_resizeFlag(true)
    ,m_borderWidth(8)
    ,m_bgColor(Qt::white)
    ,m_borderColor(Qt::white)
    ,m_resizeEnable(false)
    ,m_cursorShape(None)
{

}

WMWindowData::~WMWindowData()
{

}

void WMWindowData::init()
{

}

void WMWindowData::drawWindowEdge(QPainter *painter)
{
    if(m_parent && painter)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(m_borderWidth, m_borderWidth, m_parent->width()-2*m_borderWidth, m_parent->height()-2*m_borderWidth);

        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->fillPath(path, QBrush(Qt::white));

        /* Draw Corner shadow. */
        QRadialGradient lt_gradient(QPointF(m_borderWidth,m_borderWidth),m_borderWidth);
        lt_gradient.setColorAt(0,QColor(0,0,0,40));
        lt_gradient.setColorAt(0.5,QColor(0,0,0,15));
        lt_gradient.setColorAt(1.0,QColor(0,0,0,0));
        QBrush lt_brush(lt_gradient);
        QRect lt(0,0,m_borderWidth,m_borderWidth);
        painter->fillRect(lt,lt_brush);

        QRadialGradient rt_gradient(QPointF(m_parent->width()-m_borderWidth,m_borderWidth),m_borderWidth);
        rt_gradient.setColorAt(0,QColor(0,0,0,40));
        rt_gradient.setColorAt(0.5,QColor(0,0,0,15));
        rt_gradient.setColorAt(1.0,QColor(0,0,0,0));
        QBrush rt_brush(rt_gradient);
        QRect rt(m_parent->width()-m_borderWidth,0,m_borderWidth,m_borderWidth);
        painter->fillRect(rt,rt_brush);

        QRadialGradient lb_gradient(QPointF(m_borderWidth,m_parent->height()-m_borderWidth),m_borderWidth);
        lb_gradient.setColorAt(0,QColor(0,0,0,40));
        lb_gradient.setColorAt(0.5,QColor(0,0,0,15));
        lb_gradient.setColorAt(1.0,QColor(0,0,0,0));
        QBrush lb_brush(lb_gradient);
        QRect lb(0,m_parent->height()-m_borderWidth,m_borderWidth,m_borderWidth);
        painter->fillRect(lb,lb_brush);

        QRadialGradient rb_gradient(QPointF(m_parent->width()-m_borderWidth,m_parent->height()-m_borderWidth),m_borderWidth);
        rb_gradient.setColorAt(0,QColor(0,0,0,40));
        rb_gradient.setColorAt(0.5,QColor(0,0,0,15));
        rb_gradient.setColorAt(1.0,QColor(0,0,0,0));
        QBrush rb_brush(rb_gradient);
        QRect rb(m_parent->width()-m_borderWidth,m_parent->height()-m_borderWidth,m_borderWidth,m_borderWidth);
        painter->fillRect(rb,rb_brush);

        /* Draw frame shadow. */
        QLinearGradient top_gradient(QPoint(m_borderWidth,0),QPoint(m_borderWidth,m_borderWidth));
        top_gradient.setColorAt(0,QColor(0,0,0,0));
        top_gradient.setColorAt(0.5,QColor(0,0,0,15));
        top_gradient.setColorAt(1.0,QColor(0,0,0,40));
        QBrush top_brush(top_gradient);
        QRect top(m_borderWidth,0,m_parent->width()-2*m_borderWidth,m_borderWidth);
        painter->fillRect(top,top_brush);

        QLinearGradient bottom_gradient(QPoint(m_borderWidth,m_parent->height()-m_borderWidth),QPoint(m_borderWidth,m_parent->height()));
        bottom_gradient.setColorAt(0,QColor(0,0,0,40));
        bottom_gradient.setColorAt(0.5,QColor(0,0,0,15));
        bottom_gradient.setColorAt(1.0,QColor(0,0,0,0));
        QBrush bottom_brush(bottom_gradient);
        QRect bottom(m_borderWidth,m_parent->height()-m_borderWidth,m_parent->width()-2*m_borderWidth,m_borderWidth);
        painter->fillRect(bottom,bottom_brush);

        QLinearGradient left_gradient(QPoint(0,m_borderWidth),QPoint(m_borderWidth,m_borderWidth));
        left_gradient.setColorAt(0,QColor(0,0,0,0));
        left_gradient.setColorAt(0.5,QColor(0,0,0,15));
        left_gradient.setColorAt(1.0,QColor(0,0,0,45));
        QBrush left_brush(left_gradient);
        QRect left(0,m_borderWidth,m_borderWidth,m_parent->height()-2*m_borderWidth);
        painter->fillRect(left,left_brush);

        QLinearGradient right_gradient(QPoint(m_parent->width()-m_borderWidth,m_borderWidth),QPoint(m_parent->width(),m_borderWidth));
        right_gradient.setColorAt(0,QColor(0,0,0,45));
        right_gradient.setColorAt(0.5,QColor(0,0,0,15));
        right_gradient.setColorAt(1.0,QColor(0,0,0,0));
        QBrush right_brush(right_gradient);
        QRect right(m_parent->width()-m_borderWidth,m_borderWidth,m_borderWidth,m_parent->height()-2*m_borderWidth);
        painter->fillRect(right,right_brush);
    }
}

void WMWindowData::drawBackground(QPainter *painter)
{
    Q_UNUSED(painter)
}

void WMWindowData::mouseMoveEvent(QMouseEvent *event)
{

    if(m_parent && m_resizeEnable && m_mousePressEnable)
    {
        QPoint deltp = event->globalPos() - m_pressGlobalPoint;
        QRect rect(m_pressRect);
        switch(m_cursorShape)
        {
        case Top:
            rect.setY(m_pressRect.y()+deltp.y());
            rect.setHeight(m_pressRect.height()-deltp.y());
            break;
        case Bottom:
            if(rect.height() < m_parent->minimumHeight())
                return ;
            rect.setHeight(m_pressRect.height()+deltp.y());
            break;
        case Left:
            rect.setX(m_pressRect.x()+deltp.x());
            rect.setWidth(m_pressRect.width()-deltp.x());
            break;
        case Right:
            rect.setWidth(m_pressRect.width()+deltp.x());
            break;
        case LeftTop:
            rect.setX(m_pressRect.x()+deltp.x());
            rect.setY(m_pressRect.y()+deltp.y());
            rect.setWidth(m_pressRect.width()-deltp.x());
            rect.setHeight(m_pressRect.height()-deltp.y());
            break;
        case RightTop:
            rect.setY(m_pressRect.y()+deltp.y());
            rect.setWidth(m_pressRect.width()+deltp.x());
            rect.setHeight(m_pressRect.height()-deltp.y());
            break;
        case LeftBottom:
            rect.setX(m_pressRect.x()+deltp.x());
            rect.setWidth(m_pressRect.width()-deltp.x());
            rect.setHeight(m_pressRect.height()+deltp.y());
            break;
        case RightBottom:
            rect.setWidth(m_pressRect.width()+deltp.x());
            rect.setHeight(m_pressRect.height()+deltp.y());
            break;
        case None:
            return ;
        }

        if(rect.width() <= m_parent->minimumWidth())
            rect.setX(m_pressRect.x()+m_pressRect.width()-m_parent->minimumWidth());

        if(rect.height() <= m_parent->minimumHeight())
            rect.setY(m_pressRect.y()+m_pressRect.height()-m_parent->minimumHeight());

        m_parent->setGeometry(rect);
        return ;
    }

    if(m_parent && m_resizeFlag)
    {
        if(event->x()>=0 && event->x()<=m_borderWidth && event->y()>=0 && event->y() <= m_borderWidth)
        {
            m_resizeEnable = true;
            m_cursorShape = LeftTop;
            m_parent->setCursor(Qt::SizeFDiagCursor);
        }
        else if(event->x()>=m_borderWidth && event->x()<=(m_parent->width()-m_borderWidth) && event->y()>=0 && event->y() <= m_borderWidth)
        {
            m_resizeEnable = true;
            m_cursorShape = Top;
            m_parent->setCursor(Qt::SizeVerCursor);
        }
        else if(event->x()>=(m_parent->width()-m_borderWidth) && event->x()<=m_parent->width() && event->y()>=0 && event->y() <= m_borderWidth)
        {
            m_resizeEnable = true;
            m_cursorShape = RightTop;
            m_parent->setCursor(Qt::SizeBDiagCursor);
        }
        else if(event->x()>=0 && event->x()<=m_borderWidth && event->y()>=m_borderWidth && event->y() <= (m_parent->height()-m_borderWidth))
        {
            m_resizeEnable = true;
            m_cursorShape = Left;
            m_parent->setCursor(Qt::SizeHorCursor);
        }
        else if(event->x()>(m_parent->width()-m_borderWidth) && event->x()<=m_parent->width() && event->y() <= (m_parent->height()-m_borderWidth))
        {
            m_resizeEnable = true;
            m_cursorShape = Right;
            m_parent->setCursor(Qt::SizeHorCursor);
        }
        else if(event->x()>=0 && event->x()<=m_borderWidth && event->y()>=(m_parent->height()-m_borderWidth) && event->y() <= m_parent->height())
        {
            m_resizeEnable = true;
            m_cursorShape = LeftBottom;
            m_parent->setCursor(Qt::SizeBDiagCursor);
        }
        else if(event->x()>=m_borderWidth && event->x()<=(m_parent->width()-m_borderWidth) && event->y()>=(m_parent->height()-m_borderWidth) && event->y() <= m_parent->height())
        {
            m_resizeEnable = true;
            m_cursorShape = Bottom;
            m_parent->setCursor(Qt::SizeVerCursor);
        }
        else if(event->x()>=(m_parent->width()-m_borderWidth) && event->x()<=m_parent->width() && event->y()>=(m_parent->height()-m_borderWidth) && event->y() <= m_parent->height())
        {
            m_resizeEnable = true;
            m_cursorShape = RightBottom;
            m_parent->setCursor(Qt::SizeFDiagCursor);
        }
        else
        {
            enterEdge = false;
            m_resizeEnable = false;
            m_cursorShape = None;
            m_parent->setCursor(Qt::ArrowCursor);
        }
    }

    if (m_parent && m_mousePressEnable && (event->buttons() && Qt::LeftButton))
    {
        m_parent->move(event->globalPos() - m_mousePressPoint);
        event->accept();
    }
}

void WMWindowData::mousePressEvent(QMouseEvent *event)
{
    if (m_parent && event->button() == Qt::LeftButton)
    {
        m_mousePressEnable = true;
        m_mousePressPoint = event->globalPos() - m_parent->pos();
        m_pressGlobalPoint = event->globalPos();
        m_pressRect = m_parent->geometry();
        event->accept();
    }
}

void WMWindowData::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_mousePressEnable = false;
}

void WMWindowData::mouseDoubleEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void WMWindowData::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)

#ifdef Q_OS_WIN
    MSG *msg = (MSG *)message;
    if(msg->message==WM_MOUSEMOVE && !m_mousePressEnable)
    {
        QMouseEvent e(QEvent::MouseMove,m_parent->mapFromGlobal(QCursor::pos()),\
                      Qt::NoButton,Qt::NoButton,Qt::NoModifier);
        mouseMoveEvent(&e);
    }
#endif
}

void WMWindowData::enterEvent(QEvent *event)
{
    enterEdge = true;
    Q_UNUSED(event)
}

void WMWindowData::leaveEvent(QEvent *event)
{
    enterEdge = false;
    Q_UNUSED(event)
}

void WMWindowData::update()
{
    if(m_parent)
        m_parent->update();
}

void WMWindowData::setParent(QWidget *parent)
{
    m_parent = parent;
}
