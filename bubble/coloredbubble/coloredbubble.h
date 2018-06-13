#ifndef COLOREDBUBBLE_H
#define COLOREDBUBBLE_H

#include <QMap>
#include <QPixmap>
#include <abstractbubble.h>
#include <wmglobal.h>

class WM_EXPORT ColoredBubble : public AbstractBubble
{
public:
    ColoredBubble(const QPixmap &pixmap,int px1,int px2,\
                  int py1,int py2,const QColor &color,const QString &n);

    void appendTile(const BubbleTile &tile);
    void appendTiles(const QList<BubbleTile> &list);

    void removeTile(const BubbleTile &tile);
protected:
    QPixmap merge(const QRectF &r,const QMarginsF &m);

    void drawBase(const QRectF &r,QPainter *painter);
    void drawTils(const QList<BubbleTile> &tiles,const QRectF &r,QPainter *painter);
    void drawUps(const QRectF &r,QPainter *painter);
    void drawDowns(const QRectF &r,QPainter *painter);
private:
    QList<BubbleTile> tiles;
    QColor bgColor;
};

WM_EXPORT AbstractBubble *parserColoredBubble(const QString &fileName,QString &error);


#endif // COLOREDBUBBLE_H
