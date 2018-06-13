#include "scrollbutton.h"

#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

#define PI          3.1415926

class ScrollOptionPrivate
{
public:
    ScrollOptionPrivate()
        :m_enable(true)
        ,m_scrollSutton(0)
        ,m_radius(7.0)
    {}

    QPixmap m_pixmap;
    bool m_enable;
    double m_radius;
    ScrollButton *m_scrollSutton;
};

ScrollOption::ScrollOption(QObject *parent)
    :QObject(parent)
{
    p_d = new ScrollOptionPrivate;
}

ScrollOption::~ScrollOption()
{
    delete p_d;
}

QPixmap ScrollOption::pixmap()const
{
    return p_d->m_pixmap;
}

void ScrollOption::setPixmap(const QPixmap &pixmap)
{
    p_d->m_pixmap = pixmap;
    if(p_d->m_scrollSutton)
        p_d->m_scrollSutton->update();
}

bool ScrollOption::enable()const
{
    return p_d->m_enable;
}

void ScrollOption::setEnable(bool enable)
{
    p_d->m_enable = enable;
    if(p_d->m_scrollSutton)
        p_d->m_scrollSutton->update();
}

double ScrollOption::radius() const
{
    return p_d->m_radius;
}

void ScrollOption::setRadius(double radius)
{
    p_d->m_radius = radius;
    if(p_d->m_scrollSutton)
        p_d->m_scrollSutton->update();
}

ScrollButton *ScrollOption::scrollButton()
{
    return p_d->m_scrollSutton;
}

void ScrollOption::setScrollButton(ScrollButton *button)
{
    p_d->m_scrollSutton = button;
    if(p_d->m_scrollSutton)
        p_d->m_scrollSutton->update();
}

void ScrollOption::draw(const QPointF &point,QPainter *painter)
{
    painter->save();
    QRectF rect(point.x()-p_d->m_radius,\
                point.y()-p_d->m_radius,\
                2*p_d->m_radius,2*p_d->m_radius);
//    painter->drawPixmap(rect,p_d->m_pixmap,p_d->m_pixmap.rect());
    painter->drawText(rect,"AA");
    painter->restore();
}

struct ScrollOptionDrawData
{
    ScrollOptionDrawData(ScrollOption *o = 0)
        :option(o)
        ,transparent(1.0)
    {}
    ScrollOption *option;
    QPointF point;
    float transparent;
    QRectF rect;
};

class ScrollButtonPrivate
{
public:
    ScrollButtonPrivate()
        :m_block(ScrollButton::LeftTop)
        ,m_index(1)
        ,m_currentIndex(0)
        ,m_buttonPixmap(":/res/icon_setup_normal.png")
        ,m_scaleNumber(3)
        ,m_scrollBarColor(Qt::lightGray)
        ,m_deltAngle(0.0)
        ,m_startAngle(0*16)
        ,m_spanAngle(90*16)
        ,m_radius(46)
        ,m_mousePress(false)
        ,m_moveAngle(0.0)
        ,m_menu(0)
        ,m_scrollBarWidth(25)
        ,m_scrollBarBorderColor(Qt::gray)
        ,m_scrollBarBorder(2.0)
        ,m_buttonColor(Qt::green)
        ,m_buttonBorderColor(Qt::lightGray)
        ,m_buttonBorder(2)
    {}

    ScrollButton::Block m_block;
    int m_index;
    int m_currentIndex;
    QPixmap m_buttonPixmap;
    int m_scaleNumber;
    QColor m_scrollBarColor;
    double m_deltAngle;
    int m_startAngle;
    int m_spanAngle;
    double m_radius;
    bool m_mousePress;
    QPoint m_pressPoint;
    QPoint m_originalPoint;
    double m_moveAngle;

    int m_scrollBarWidth;
    QColor m_scrollBarBorderColor;
    double m_scrollBarBorder;
    QColor m_buttonColor;
    QColor m_buttonBorderColor;
    int m_buttonBorder;
    QList<ScrollOption *> m_optionList;
    QList<ScrollOptionDrawData *> m_optDrawList;
    QMenu *m_menu;

    void update_postion(double height);
    void update_move_angle(double height,const QPoint &o,const QPoint &pos);
};

void ScrollButtonPrivate::update_postion(double height)
{
    m_deltAngle = (0.5 * PI) / m_scaleNumber;
    m_startAngle = m_index * m_deltAngle;

    int j=m_index;
    for(int i=m_currentIndex;i>=0;i-- && j--)
    {
        double x = m_radius * cos(j*m_deltAngle+m_moveAngle);
        double y = height - m_radius * sin(j*m_deltAngle+m_moveAngle);
        m_optDrawList.at(i)->point = QPointF(x,y);
    }

    j=m_index+1;
    for(int i=(m_currentIndex+1);i<m_optDrawList.count();i++ && j++)
    {
        double x = m_radius * cos(j*m_deltAngle+m_moveAngle);
        double y = height - m_radius * sin(j*m_deltAngle+m_moveAngle);
        m_optDrawList.at(i)->point = QPointF(x,y);
    }
}

void ScrollButtonPrivate::update_move_angle(double height,const QPoint &o,const QPoint &pos)
{
    double angle_a;
    if(pos.x()!=o.x())
        angle_a = atan(((double)pos.y()-o.y())/(pos.x()-o.x()));
    else
        angle_a = 0.5 * PI;

    double angle_b;
    if(m_pressPoint.x()!=o.x())
        angle_b = atan(((double)m_pressPoint.y()-o.y())/(m_pressPoint.x()-o.x()));
    else
        angle_b = 0.5 * PI;

    m_moveAngle = (angle_b - angle_a);
    update_postion(height);
}

ScrollButton::ScrollButton(QWidget *parent)
    : QWidget(parent)
{
    p_d = new ScrollButtonPrivate;
}

ScrollButton::~ScrollButton()
{
    delete p_d;
}

ScrollButton::Block ScrollButton::block() const
{
    return p_d->m_block;
}

void ScrollButton::setBlock(ScrollButton::Block block)
{
    p_d->m_block = block;
    switch(p_d->m_block)
    {
    case LeftTop:
        p_d->m_startAngle = 0*16;
        p_d->m_startAngle = 90*16;
        p_d->m_originalPoint.setX(0);
        p_d->m_originalPoint.setY(height());
        break;
    case RightTop:
        p_d->m_startAngle = 90*16;
        p_d->m_startAngle = 180*16;
        p_d->m_originalPoint.setX(width());
        p_d->m_originalPoint.setY(height());
        break;
    case LeftBottom:
        p_d->m_startAngle = 270*16;
        p_d->m_startAngle = 360*16;
        p_d->m_originalPoint.setX(width());
        p_d->m_originalPoint.setY(0);
        break;
    case RightBottom:
        p_d->m_startAngle = 180*16;
        p_d->m_startAngle = 270*16;
        p_d->m_originalPoint.setX(0);
        p_d->m_originalPoint.setY(0);
        break;
    }
    update();
}

int ScrollButton::index() const
{
    return p_d->m_index;
}

void ScrollButton::setIndex(int index)
{
    if((index+1)<p_d->m_scaleNumber)
    {
        p_d->m_index = index;
        update();
    }
}

QPixmap ScrollButton::buttonPixmap() const
{
    return p_d->m_buttonPixmap;
}

void ScrollButton::setButtonPixmap(const QPixmap &pixmap)
{
    p_d->m_buttonPixmap = pixmap;
    update();
}

int ScrollButton::scaleNumber() const
{
    return p_d->m_scaleNumber;
}

void ScrollButton::setScaleNumber(int number)
{
    p_d->m_scaleNumber = number;
    update();
}

QColor ScrollButton::scrollBarColor() const
{
    return p_d->m_scrollBarColor;
}

void ScrollButton::setScrollBarColor(const QColor &color)
{
    p_d->m_scrollBarColor = color;
    update();
}

int ScrollButton::scrollBarWidth() const
{
    return p_d->m_scrollBarWidth;
}

void ScrollButton::setScrollBarWidth(int width)
{
    p_d->m_scrollBarWidth = width;
}

QColor ScrollButton::scrollBarBorderColor() const
{
    return p_d->m_scrollBarBorderColor;
}

void ScrollButton::setScrollBarBorderColor(const QColor &color)
{
    p_d->m_scrollBarBorderColor = color;
    update();
}

int ScrollButton::scrollBarBorder() const
{
    return p_d->m_scrollBarBorder;
}

void ScrollButton::setScrollBarBorder(int border)
{
    p_d->m_scrollBarBorder = border;
    update();
}

QColor ScrollButton::buttonColor() const
{
    return p_d->m_buttonColor;
}

void ScrollButton::setButtonColor(const QColor &color)
{
    p_d->m_buttonColor = color;
}

QColor ScrollButton::buttonBorderColor() const
{
    return p_d->m_buttonBorderColor;
}

void ScrollButton::setButtonBorderColor(const QColor &color)
{
    p_d->m_buttonBorderColor = color;
    update();
}

int ScrollButton::buttonBorder() const
{
    return p_d->m_buttonBorder;
}

void ScrollButton::setButtonBorder(int border)
{
    p_d->m_buttonBorder = border;
    update();
}

void ScrollButton::appendOptions(const QList<ScrollOption *> &list)
{
    p_d->m_optionList.append(list);

    foreach(ScrollOption * option,list)
        p_d->m_optDrawList.append(new ScrollOptionDrawData(option));

    p_d->update_postion(height());
    update();
}

void ScrollButton::appendOption(ScrollOption *option)
{
    p_d->m_optionList.append(option);
    p_d->m_optDrawList.append(new ScrollOptionDrawData(option));

    p_d->update_postion(height());
    update();
}

QList<ScrollOption *> ScrollButton::options()
{
    return p_d->m_optionList;
}

const QList<ScrollOption *> ScrollButton::options() const
{
    return p_d->m_optionList;
}

QMenu *ScrollButton::menu() const
{
    return p_d->m_menu;
}

void ScrollButton::setMenu(QMenu *menu)
{
    p_d->m_menu = menu;
    update();
}

void ScrollButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.save();
    /* Draw Scall Bar Border. */
    painter.setPen(QPen(QBrush(p_d->m_scrollBarBorderColor),\
                        p_d->m_scrollBarBorder));
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    /* Inside Border. */
    QRectF inRect(p_d->m_scrollBarBorder+p_d->m_scrollBarWidth-width(),\
             p_d->m_scrollBarBorder+p_d->m_scrollBarWidth,\
             2*(width()-p_d->m_scrollBarWidth-p_d->m_scrollBarBorder),\
             2*(height()-p_d->m_scrollBarWidth-p_d->m_scrollBarBorder));
    painter.fillRect(inRect,p_d->m_buttonColor);
    painter.drawArc(inRect,p_d->m_startAngle,p_d->m_spanAngle);

    /* Outside Border. */
    QRectF outRect(p_d->m_scrollBarBorder/2-width(),\
             p_d->m_scrollBarBorder/2,\
             2*width()-p_d->m_scrollBarBorder,\
             2*height()-p_d->m_scrollBarBorder);
    painter.drawArc(outRect,p_d->m_startAngle,p_d->m_spanAngle);
    painter.restore();

    painter.save();
    /* Draw Scall Bar. */
    painter.setPen(QPen(QBrush(p_d->m_scrollBarColor),\
                        p_d->m_scrollBarWidth));
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    QRectF sbRect(p_d->m_scrollBarBorder+p_d->m_scrollBarWidth/2-width(),\
             p_d->m_scrollBarBorder+p_d->m_scrollBarWidth/2,\
             2*(width()-p_d->m_scrollBarWidth/2-p_d->m_scrollBarBorder),\
             2*(height()-p_d->m_scrollBarWidth/2-p_d->m_scrollBarBorder));
    painter.drawArc(sbRect,p_d->m_startAngle,p_d->m_spanAngle);
    painter.restore();

    painter.save();
    /* Draw Scroll Option. */
    foreach(ScrollOptionDrawData *data,p_d->m_optDrawList)
    {
        qDebug() << data->point << " " << p_d->m_radius;
        data->option->draw(data->point,&painter);
    }
    painter.restore();

    painter.save();
    /* Draw Button Pixmap. */
    QRectF btnRect(2,height()-2-20,20,20);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(btnRect,p_d->m_buttonPixmap,p_d->m_buttonPixmap.rect());
    painter.restore();

    QWidget::paintEvent(event);
}

void ScrollButton::mouseMoveEvent(QMouseEvent *event)
{
    if(p_d->m_mousePress)
    {
        QPoint p = event->pos();
        p_d->update_move_angle(height(),QPoint(0,height()),p);
    }
    update();
//    QWidget::mouseMoveEvent(event);
}

void ScrollButton::mousePressEvent(QMouseEvent *event)
{
    p_d->m_mousePress = true;
    p_d->m_pressPoint = event->pos();
//    QWidget::mousePressEvent(event);
}

void ScrollButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(abs(p_d->m_moveAngle) > p_d->m_deltAngle)
    {
        int delt = p_d->m_moveAngle / p_d->m_deltAngle;
        if(delt)
        {
            p_d->m_currentIndex -= delt;
            if((p_d->m_currentIndex+1) > p_d->m_optDrawList.count())
                p_d->m_currentIndex = p_d->m_optDrawList.count()-1;
            if(p_d->m_currentIndex<0)
                p_d->m_currentIndex = 0;
        }
        qDebug() << p_d->m_moveAngle << p_d->m_deltAngle << p_d->m_currentIndex;


    }
    p_d->m_moveAngle = 0;
    p_d->update_postion(height());
    update();
    p_d->m_mousePress = false;
//    QWidget::mouseReleaseEvent(event);
}

void ScrollButton::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0)
        p_d->m_currentIndex--;
    else
        p_d->m_currentIndex++;

    if((p_d->m_currentIndex+1) > p_d->m_optDrawList.count())
        p_d->m_currentIndex = p_d->m_optDrawList.count()-1;
    if(p_d->m_currentIndex<0)
        p_d->m_currentIndex = 0;
    qDebug() << "wheel" ;
    p_d->update_postion(height());
    update();
    QWidget::wheelEvent(event);
}

void ScrollButton::resizeEvent(QResizeEvent *event)
{
    p_d->m_radius = width()-p_d->m_scrollBarBorder-p_d->m_scrollBarWidth/2;
    QWidget::resizeEvent(event);
}
