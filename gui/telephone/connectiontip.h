#ifndef CONNECTIONTIP_H
#define CONNECTIONTIP_H

#include <QWidget>

namespace Ui {
class ConnectionTip;
}

class ConnectionTip : public QWidget
{
    Q_OBJECT

public:
    enum State
    {
        Normal,
        Unormal
    };

    explicit ConnectionTip(QWidget *parent = 0);
    ~ConnectionTip();

    void show();

    void setSpeakerState(State state,const QString &desc = "");
    void setMicrophoneState(State state,const QString &desc = "");
    void setCameraState(State state,const QString &desc = "");
    void setNetworkState(State state,const QString &desc = "");
    void setSystemState(State state,const QString &desc = "");
protected:
    void focusOutEvent(QFocusEvent *event);
private:
    Ui::ConnectionTip *ui;
};

#endif // CONNECTIONTIP_H
