#include "toolbaraction.h"

#include <QDebug>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>


class ToolBarActionPrivate
{
public:
    ToolBarActionPrivate()
        :m_iconPath(":/res/talk/nnu.png")
        ,m_iconPixmap(m_iconPath)
        ,m_menuWidth(15)
        ,m_iconWidth(16)
        ,m_iconHeight(16)
        ,m_bgColor(Qt::white)
        ,m_normalBgColor(Qt::white)
        ,m_hoverBgColor(Qt::gray)
        ,m_pressedBgColor(Qt::darkGray)
        ,m_indicatorPressed(false)
        ,m_mousePressed(false)
    {}
    QString m_iconPath;
    QPixmap m_iconPixmap;
    QString m_pixmapPath;
    QPixmap m_pixmap;
    int m_menuWidth;
    int m_iconWidth;
    int m_iconHeight;
    QRect m_iconRect;
    QColor m_bgColor;
    QColor m_normalBgColor;
    QColor m_hoverBgColor;
    QColor m_pressedBgColor;
    bool m_indicatorPressed;
    bool m_mousePressed;
    QString m_menuStyleSheet;
};

ToolBarAction::ToolBarAction(QWidget *parent) :
    QWidget(parent)
{
    p_d = new ToolBarActionPrivate;
    setMouseTracking(true);
    p_d->m_iconRect = QRect();
    setFocusPolicy(Qt::ClickFocus);
    QPalette p = palette();
    p.setColor(QPalette::AlternateBase,Qt::gray);
}

ToolBarAction::~ToolBarAction()
{
    delete p_d;
}

QString ToolBarAction::iconPath() const
{
    return p_d->m_iconPath;
}

void ToolBarAction::setIconPath(const QString &path)
{
    p_d->m_iconPath = path;
    update();
}

QPixmap ToolBarAction::icon() const
{
    return p_d->m_iconPixmap;
}

void ToolBarAction::setIcon(const QPixmap &pixmap)
{
    p_d->m_iconPixmap = pixmap;
}

QPixmap ToolBarAction::pixmap() const
{
    return p_d->m_pixmap;
}

void ToolBarAction::setPixmap(const QPixmap &pixmap)
{
    p_d->m_pixmap = pixmap;
    update();
}

void ToolBarAction::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.fillRect(rect(),p_d->m_bgColor);
    if(!p_d->m_iconPixmap.isNull())
    {
        painter.drawPixmap(p_d->m_iconRect,p_d->m_iconPixmap.scaled(QSize(p_d->m_iconRect.width(),p_d->m_iconRect.height()),Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    if(!p_d->m_pixmap.isNull())
    {
        painter.drawPixmap(p_d->m_iconRect,p_d->m_iconPixmap.scaled(QSize(p_d->m_iconWidth,p_d->m_iconHeight),Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    QWidget::paintEvent(event);
}

void ToolBarAction::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    QPoint point(0,height());
    p_d->m_mousePressed = true;
    if(p_d->m_indicatorPressed)
    {
        p_d->m_indicatorPressed = false;
        p_d->m_bgColor = p_d->m_hoverBgColor;
        emit clicked();
        return ;
    }
    if(event->x()>(width()-p_d->m_iconWidth))
    {
        p_d->m_indicatorPressed = true;
        emit indicatorClick();
        QMenu menu(this);
        menu.setStyleSheet(p_d->m_menuStyleSheet);
        menu.exec(actions(),mapToGlobal(point));
        p_d->m_indicatorPressed = false;
        QPoint p = mapFromGlobal(QCursor::pos());
        if(p.x()>0 && p.x()<(width()-p_d->m_iconWidth) && p.x()>0 && p.y() <height())
            p_d->m_bgColor = p_d->m_hoverBgColor;
        else
            p_d->m_bgColor = p_d->m_normalBgColor;
        repaint();
    }
    else
    {
        emit clicked();
    }
}

void ToolBarAction::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}

void ToolBarAction::mouseReleaseEvent(QMouseEvent *event)
{
    p_d->m_mousePressed = false;
    if(rect().contains(event->pos()))
    {
        emit pressed();
        if(!p_d->m_indicatorPressed)
            p_d->m_bgColor = p_d->m_hoverBgColor;
    }
    else
        p_d->m_bgColor = p_d->m_normalBgColor;
    update();
    QWidget::mouseReleaseEvent(event);
}

void ToolBarAction::resizeEvent(QResizeEvent *event)
{
    int w = p_d->m_iconPixmap.width();
    int h = p_d->m_iconPixmap.height();
    if(p_d->m_iconHeight<=p_d->m_iconPixmap.height())
    {
        double delt = p_d->m_iconPixmap.width()/(double)p_d->m_iconPixmap.height();
        w = delt*p_d->m_iconHeight;
        h = p_d->m_iconHeight;
    }
    if(p_d->m_iconWidth<=p_d->m_iconPixmap.width())
    {
        double delt = p_d->m_iconPixmap.height()/(double)p_d->m_iconPixmap.width();
        w = p_d->m_iconWidth;
        h = delt*p_d->m_iconWidth;
    }
    p_d->m_iconRect = QRect(event->size().width()-w,\
                            event->size().height()/2-h/2,\
                            w,h);
    update();
    QWidget::resizeEvent(event);
}

void ToolBarAction::enterEvent(QEvent *event)
{
    p_d->m_bgColor = p_d->m_hoverBgColor;
    update();
    QWidget::enterEvent(event);
}

void ToolBarAction::leaveEvent(QEvent *event)
{
    if(!p_d->m_indicatorPressed)
    {
        p_d->m_bgColor = p_d->m_normalBgColor;
        repaint();
    }
    QWidget::leaveEvent(event);
}

void ToolBarAction::focusInEvent(QFocusEvent *event)
{
    p_d->m_bgColor = p_d->m_pressedBgColor;
    QWidget::focusInEvent(event);
}

void ToolBarAction::focusOutEvent(QFocusEvent *event)
{
    if(p_d->m_indicatorPressed && p_d->m_mousePressed)
    {
        p_d->m_bgColor = p_d->m_pressedBgColor;
        repaint();
    }
    else
    {
        p_d->m_indicatorPressed = false;
        p_d->m_bgColor = p_d->m_normalBgColor;
        repaint();
    }
    QWidget::focusOutEvent(event);
}
