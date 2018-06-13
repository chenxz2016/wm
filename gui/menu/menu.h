#ifndef MENU_H
#define MENU_H

#include <QMenu>

#include <QGraphicsEffect>

class MenuGraphicEffect : public QGraphicsEffect
{
    Q_OBJECT
public:
    MenuGraphicEffect(QObject *parent = 0)
        :QGraphicsEffect(parent)
        ,width(7)
        ,radius(3)
    {}

protected:
    void draw(QPainter *painter);
private:
    qreal width;
    qreal radius;
};

class Menu : public QMenu
{
public:
    Menu(QWidget *parent = 0);

    static QMenu *createMenu(QWidget *parent);
private:
    class MenuPrivate *p_d;
};

#endif // MENU_H
