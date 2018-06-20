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
private:
    class CSLoginProcessPrivate *p_d;
    friend class CSLoginProcessPrivate;
};


class CSLoginKeyProcess : public AbstractCSProcess
{
    Q_OBJECT
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout)
public:
    enum CSLoginStatus
    {
        Offline,
        Online,
        Leave,
        Hide,
        Bussy
    };

    explicit CSLoginKeyProcess(ClientService *parent = 0);
    ~CSLoginKeyProcess();

    bool syncRecv(wm_parameter_t *param,quint16 param_num);
    bool syncSend(const QVariant &data);

    void ayncRecv(wm_parameter_t *param,quint16 param_num);
    void ayncSend(const QVariant &data);

    WMEncryptKey publicKey() const;
    WMEncryptKey privateKey() const;

    void setTimeout(int timeout);
    int timeout()const;
protected:
    void timerEvent(QTimerEvent *event);
private:
    class CSLoginKeyProcessPrivate *p_d;
    friend class CSLoginKeyProcessPrivate;
};

#endif // CSLOGINPROCESS_H
