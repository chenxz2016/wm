#include "videocall.h"
#include "ui_videocall.h"
#include "videocallwarning.h"

#include <QMenu>
#include <QVideoWidget>


class VideoCallPrivate
{
public:
    VideoCallPrivate(VideoCall *parent)
        :p(parent)
    {}

    void init()
    {
        p->ui->setupUi(p);
    }

    VideoCall *p;

    QSlider *volumn;
    VideoCallWarning *warning;
    QMenu *more;
    QVideoWidget *other;
};

VideoCall::VideoCall(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoCall),
    p_d(new VideoCallPrivate(this))
{
    p_d->init();
}

VideoCall::~VideoCall()
{
    delete ui;
    delete p_d;
}
