#ifndef WMWINDOWDATA_H
#define WMWINDOWDATA_H

#include <QPoint>
#include <QColor>
#include <QRect>

class QWidget;
class QPainter;
class QMouseEvent;
class QEvent;

class WMWindowData
{
public:
    WMWindowData(QWidget *parent = 0);
    virtual ~WMWindowData();

    virtual void init();

    virtual void drawWindowEdge(QPainter *painter);
    virtual void drawBackground(QPainter *painter);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleEvent(QMouseEvent *event);
    virtual void nativeEvent(const QByteArray &eventType, void *message, long *result);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);

    void update();
    void setParent(QWidget *parent);

    enum ResizeType
    {
        Top,
        Bottom,
        Left,
        Right,
        LeftTop,
        RightTop,
        LeftBottom,
        RightBottom,
        None
    };
    QPoint m_mousePressPoint;
    QPoint m_mouseReleasePoint;
    QPoint m_pressGlobalPoint;
    QRect m_pressRect;
    bool m_mousePressEnable;
    bool m_resizeEnable;
    bool m_resizeFlag;
    QWidget *m_parent;
    int m_borderWidth;
    QColor m_bgColor;
    QColor m_borderColor;
    ResizeType m_cursorShape;
    bool enterEdge;
};

#endif // WMWINDOWDATA_H
