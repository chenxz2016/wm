#ifndef SCROLLBUTTON_H
#define SCROLLBUTTON_H

#include <QWidget>

class QMenu;
class ScrollButton;
class ScrollOption : public QObject
{
    Q_OBJECT
    friend class ScrollButton;

    Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap)
    Q_PROPERTY(bool enable READ enable WRITE setEnable)
    Q_PROPERTY(double radius READ radius WRITE setRadius)
public:
    explicit ScrollOption(QObject *parent = 0);
    ~ScrollOption();

    QPixmap pixmap()const;
    void setPixmap(const QPixmap &pixmap);

    bool enable()const;
    void setEnable(bool enable);

    double radius()const;
    void setRadius(double radius);

    ScrollButton *scrollButton();
    void setScrollButton(ScrollButton *button);

protected:
    virtual void draw(const QPointF &point,QPainter *painter);
private:
    class ScrollOptionPrivate *p_d;
};

class ScrollButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(Block block READ block WRITE setBlock)
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(QPixmap buttonPixmap READ buttonPixmap WRITE setButtonPixmap)
    Q_PROPERTY(int scaleNumber READ scaleNumber WRITE setScaleNumber)

    Q_PROPERTY(QColor scrollBarColor READ scrollBarColor WRITE setScrollBarColor)
    Q_PROPERTY(int scrollBarWidth READ scrollBarWidth WRITE setScrollBarWidth)
    Q_PROPERTY(QColor scrollBarBorderColor READ scrollBarBorderColor WRITE setScrollBarBorderColor)
    Q_PROPERTY(int scrollBarBorder READ scrollBarBorder WRITE setScrollBarBorder)
    Q_PROPERTY(QColor buttonColor READ buttonColor WRITE setButtonColor)
    Q_PROPERTY(QColor buttonBorderColor READ buttonBorderColor WRITE setButtonBorderColor)
    Q_PROPERTY(int buttonBorder READ buttonBorder WRITE setButtonBorder)
public:
    enum Block
    {
        LeftTop = 0x02,
        RightTop = 0x04,
        LeftBottom = 0x08,
        RightBottom = 0x0f
    };

    explicit ScrollButton(QWidget *parent = 0);
    ~ScrollButton();

    Block block()const;
    void setBlock(Block block);

    int index()const;
    void setIndex(int index);

    QPixmap buttonPixmap()const;
    void setButtonPixmap(const QPixmap &pixmap);

    int scaleNumber()const;
    void setScaleNumber(int number);

    QColor scrollBarColor()const;
    void setScrollBarColor(const QColor &color);

    int scrollBarWidth()const;
    void setScrollBarWidth(int width);

    QColor scrollBarBorderColor()const;
    void setScrollBarBorderColor(const QColor &color);

    int scrollBarBorder()const;
    void setScrollBarBorder(int border);

    QColor buttonColor()const;
    void setButtonColor(const QColor &color);

    QColor buttonBorderColor()const;
    void setButtonBorderColor(const QColor &color);

    int buttonBorder()const;
    void setButtonBorder(int border);


    void appendOptions(const QList<ScrollOption *> &list);
    void appendOption(ScrollOption *option);
    QList<ScrollOption *> options();
    const QList<ScrollOption *> options()const;

    QMenu *menu()const;
    void setMenu(QMenu *menu);

signals:
    void indexChanged(int index);
public slots:

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void resizeEvent(QResizeEvent *event);
private:
    class ScrollButtonPrivate *p_d;
};

#endif // SCROLLBUTTON_H
