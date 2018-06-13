#ifndef QGRAPHICSAUDIOITEM_H
#define QGRAPHICSAUDIOITEM_H

#include <QGraphicsObject>
#include <QMediaPlayer>
#include <QMovie>
#include <wmglobal.h>

class WM_EXPORT QGraphicsAudioItem : public QGraphicsObject
{
    Q_OBJECT
public:
    QGraphicsAudioItem(const QString &gif,QGraphicsItem *parent = 0);
    ~QGraphicsAudioItem();

    void setGif(const QString &gif);
    void play();
    void stop();
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public slots:
    void updateState(QMediaPlayer::MediaStatus status);
private slots:
    void repaint(int);
private:
    QMovie movie;
    QRectF br;
};

#endif // QGRAPHICSAUDIOITEM_H
