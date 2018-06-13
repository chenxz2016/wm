#ifndef CSLOGINPROCESS_H
#define CSLOGINPROCESS_H

#include "abstractcsprocess.h"
#include "clientservice.h"

class ClientService;

class CSLoginProcess : public AbstractCSProcess
{
    Q_OBJECT
    Q_PROPERTY(CSLoginStatus loginStatus READ loginStatus WRITE setLoginStatus)
    Q_PROPERTY(int loginTimeout READ loginTimeout WRITE setLoginTimeout)
public:
    enum CSLoginStatus
    {
        Offline,
        Online,
        Leave,
        Hide,
        Bussy
    };

    explicit CSLoginProcess(ClientService *parent = 0);
    ~CSLoginProcess();

    bool syncRecv(wm_parameter_t *param,quint16 param_num);
    bool syncSend(const QVariant &data);

    void ayncRecv(wm_parameter_t *param,quint16 param_num);
    void ayncSend(const QVariant &data);

    CSLoginStatus loginStatus()const;
    void setLoginStatus(CSLoginStatus status);

    void setLoginTimeout(int timeout);
    int loginTimeout()const;
protected:
    void timerEvent(QTimerEvent *event);
    void setEnryptKey(const WMEncryptKey &key);
private:
    class CSLoginProcessPrivate *p_d;
    friend class CSLoginProcessPrivate;
};

#endif // CSLOGINPROCESS_H
