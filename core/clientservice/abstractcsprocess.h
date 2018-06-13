#ifndef ABSTRACTCSPROCESS_H
#define ABSTRACTCSPROCESS_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <wm_protocol.h>

class ClientService;
class AbstractCSProcess : public QObject
{
    Q_OBJECT
public:
    AbstractCSProcess(ClientService *service);

    quint16 uniqueID()const;

    virtual bool syncRecv(wm_parameter_t *param,quint16 param_num);
    virtual bool syncSend(const QVariant &data);

    virtual void ayncRecv(wm_parameter_t *param,quint16 param_num);
    virtual void ayncSend(const QVariant &data);

    QString error()const;

    void setClientService(ClientService *service);
    ClientService *clientService()const;
	
	quint32 userID()const;
	void setUserID(quint32 id);
protected:
    void setUniqueID(quint16 id);
    void resetPushData();
    void appendPushData(const QString &key,const QVariant &d);
signals:
    void error(int,QString);
protected:
    QString p_error;
    ClientService *p_service;
    quint16 p_id;
	quint32 p_userID;
};

#endif // ABSTRACTCSPROCESS_H
