#ifndef VIDEOCALL_H
#define VIDEOCALL_H

#include <QWidget>

namespace Ui {
class VideoCall;
}

class VideoCall : public QWidget
{
    Q_OBJECT

public:
    explicit VideoCall(QWidget *parent = 0);
    ~VideoCall();

private:
    Ui::VideoCall *ui;
    class VideoCallPrivate *p_d;
    friend class VideoCallPrivate;
};

#endif // VIDEOCALL_H
