#include "abstractcsprocess.h"
#include "clientservice.h"

AbstractCSProcess::AbstractCSProcess(ClientService *service)
    :QObject(service)
    ,p_service(service)
    ,p_id(0)
{

}

quint16 AbstractCSProcess::uniqueID() const
{
    return p_id;
}

bool AbstractCSProcess::syncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
    p_error = "syncRecv not be implemented.";
    return false;

}

bool AbstractCSProcess::syncSend(const QVariant &data)
{
    Q_UNUSED(data)
    p_error = "syncSend not be implemented,";
    return false;
}

void AbstractCSProcess::ayncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
    p_error = "ayncRecv not be implemented.";
    emit error(0,p_error);
}

void AbstractCSProcess::ayncSend(const QVariant &data)
{
    Q_UNUSED(data)
    p_error = "ayncSend not be implemented.";
    emit error(0,p_error);
}


QString AbstractCSProcess::error() const
{
    return p_error;
}

void AbstractCSProcess::setClientService(ClientService *service)
{
    p_service = service;
}

ClientService *AbstractCSProcess::clientService() const
{
    return p_service;
}

void AbstractCSProcess::setUniqueID(quint16 id)
{
    p_id = id;
}

void AbstractCSProcess::resetPushData()
{
    p_service->resetData();
}

void AbstractCSProcess::appendPushData(const QString &key, const QVariant &d)
{
    p_service->setData(key,d);
}

quint32 AbstractCSProcess::userID()const
{
	return p_userID;
}

void AbstractCSProcess::setUserID(quint32 id)
{
	p_userID = id;
}
