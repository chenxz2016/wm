#include "qgraphicsaudioitem.h"

#include <QFile>
#include <QPainter>

QGraphicsAudioItem::QGraphicsAudioItem(const QString &gif,QGraphicsItem *parent)
    :QGraphicsObject(parent)
{
    movie.setDevice(new QFile(gif));
    QObject::connect(&movie,SIGNAL(finished()),&movie,SLOT(start()));
    QObject::connect(&movie,SIGNAL(frameChanged(int)),this,SLOT(repaint(int)));
}

QGraphicsAudioItem::~QGraphicsAudioItem()
{

}

void QGraphicsAudioItem::setGif(const QString &gif)
{
    movie.setDevice(new QFile(gif));
}

void QGraphicsAudioItem::play()
{
    movie.start();
}

void QGraphicsAudioItem::stop()
{
    movie.stop();
}

QRectF QGraphicsAudioItem::boundingRect()const
{
    return br;
}

void QGraphicsAudioItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    if(movie.state()==QMovie::Running)
        painter->drawPixmap(QPointF(0,0), movie.currentPixmap());
}

void QGraphicsAudioItem::updateState(QMediaPlayer::MediaStatus status)
{
    if(status==QMediaPlayer::EndOfMedia)
        movie.stop();
}

void QGraphicsAudioItem::repaint(int)
{
    QGraphicsItem::update();
}
