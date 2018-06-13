#ifndef WINDOWIMPL_H
#define WINDOWIMPL_H

#include <QPoint>
#include <QColor>
#include <QRect>

class QWidget;
class QPainter;
class QMouseEvent;
class QEvent;

class WindowImpl
{
public:
    WindowImpl(QWidget *parent);
    virtual ~WindowImpl();

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
    virtual void parentChangedEvent(QEvent *event);

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
    QPoint mousePressPoint;
    QPoint mouseReleasePoint;
    QPoint pressGlobalPoint;
    QRect pressRect;
    bool mousePressEnable;
    bool resizeEnable;
    bool resizeFlag;
    QWidget *w_p;
    int borderWidth;
    QColor bgColor;
    QColor borderColor;
    ResizeType cursorShape;
    bool enterEdge;
};

#endif // WINDOWIMPL_H
