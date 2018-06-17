#include "videoplayer.h"


class VideoPlayerPrivate
{
public:
    VideoPlayerPrivate()
        :autoPlay(true)
        ,repeatPlay(true)
    {}
    bool autoPlay;
    bool repeatPlay;
};

VideoPlayer::VideoPlayer(QObject *parent)
    : QMediaPlayer(parent)
    ,p_d(new VideoPlayerPrivate)
{
    connect(this,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(checkState(QMediaPlayer::MediaStatus)));
}

VideoPlayer::~VideoPlayer()
{
    delete p_d;
}

void VideoPlayer::setAutoPlay(bool autoPlay)
{
    p_d->autoPlay = autoPlay;
}

bool VideoPlayer::autoPlay() const
{
    return p_d->autoPlay;
}

void VideoPlayer::setRepeatPlay(bool repeat)
{
    p_d->repeatPlay = repeat;
}

bool VideoPlayer::repeatPlay() const
{
    return p_d->repeatPlay;
}

void VideoPlayer::checkState(QMediaPlayer::MediaStatus status)
{
    if(status==QMediaPlayer::EndOfMedia && p_d->repeatPlay)
        play();
}
