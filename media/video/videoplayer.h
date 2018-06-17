#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMediaPlayer>
#include <QObject>
#include <wmglobal.h>


class WM_EXPORT VideoPlayer : public QMediaPlayer
{
    Q_OBJECT
    Q_PROPERTY(bool autoPlay READ autoPlay WRITE setAutoPlay)
    Q_PROPERTY(bool repeatPlay READ repeatPlay WRITE setRepeatPlay)
public:
    explicit VideoPlayer(QObject *parent = 0);
    ~VideoPlayer();

    void setAutoPlay(bool autoPlay);
    bool autoPlay()const;

    void setRepeatPlay(bool repeat);
    bool repeatPlay()const;
private slots:
    void checkState(QMediaPlayer::MediaStatus status);
private:
    class VideoPlayerPrivate *p_d;
};

#endif // VIDEOPLAYER_H
