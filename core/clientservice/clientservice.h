#ifndef CLIENTSERVICE_H
#define CLIENTSERVICE_H

#include "abstractservice.h"
#include "wmglobal.h"
#include "wm_protocol.h"

struct WMEncryptKey
{
    char key[256];
    quint8 key_len;
    quint8 type;
    void setKey(quint8 len,const char *k,quint8 t)
    {
        memcpy(key,k,len);
        key_len = len;
        type = t;
    }
};

#define CS_SERVICE_ID 0

class WM_EXPORT ClientService : public AbstractService
{
    Q_OBJECT
public:
    explicit ClientService(QObject *parent = 0);
    ~ClientService();

    void flush(QString key);
    void flush(QVariant key);
    QByteArray name();
    QVariant getData();

    WMEncryptKey encryptKey()const;

    bool verifyAccount(quint32 id, const QByteArray &pwd)const;

    int loginStatus()const;
    void setLoginStatus(int status);

    bool startLogin(quint32 id, const QByteArray &pwd);
    QString error()const;

    bool sendData(const QByteArray &data);
    bool sendData(const char *data,quint32 data_len);

	bool sendPackage(wm_protocol_t *proto);
	
    quint32 userID()const;
    void setUserID(quint32 id);

    QByteArray pwd()const;
    void setPwd(const QByteArray &pwd);

    quint16 protoType()const;
    void localDevice(char *device);
    quint8 network()const;
    quint32 time()const;
    void protoVersion(char *version);

    quint32 protoSequence()const;
signals:
    void error(QString);
protected:
    void setEncryptKey(const WMEncryptKey &key)const;
    void setData(const QString &key,const QVariant &d);
    void resetData();
private slots:
    void tcpRead();
private:
    class ClientServicePrivate *p_d;
    friend class ClientServicePrivate;
    friend class AbstractCSProcess;
    friend class CSLoginKeyProcess;
};


#endif // CLIENTSERVICE_H
