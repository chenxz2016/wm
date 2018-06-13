#include "csmsgprocess.h"
#include "clientservice.h"
#include "wmp_message.h"

class CSMsgProcessPrivate
{
public:
    CSMsgProcessPrivate(CSMsgProcess *parent)
        :p(parent)
    {}

    void init()
    {
        p->setUniqueID(WMP_PROTO_MSG_ID);
    }

    int timeout;
    CSMsgProcess *p;
};

CSMsgProcess::CSMsgProcess(quint32 id,ClientService *parent)
    :AbstractCSProcess(parent)
    ,p_d(new CSMsgProcessPrivate(this))
{
    p_d->init();
    setUserID(id);
}

CSMsgProcess::~CSMsgProcess()
{
    delete p_d;
}

bool CSMsgProcess::syncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
    return true;
}

bool CSMsgProcess::syncSend(const QVariant &data)
{
    QMap<QString,QVariant> map = data.toMap();
    bool ok = true;
    quint32 dst = map["dst"].toString().toInt(&ok);
    if(dst<1000)
    {
        return false;
    }

    quint8 attr = map["attr"].toInt();
    if(!attr)
    {
        return true;
    }

    QByteArray msg = map["msg"].toByteArray();
    if(msg.isEmpty())
        return false;

    /* 2 parameters, user id and user pwd. */
    wm_protocol_t *proto = allocate_wmp(1);

    proto->base.proto_type = p_service->protoType();
    proto->base.src = p_userID;
    proto->base.dst = CS_SERVICE_ID;
    p_service->localDevice(proto->base.device);

    proto->base.network = p_service->network();
    proto->base.time = p_service->time();

    p_service->protoVersion(proto->base.version);

    wmp_message_t *message = allocate_wmp_message();
    set_wmp_message_len(message,msg.length());

    proto->body.param->main_id = uniqueID();
    proto->body.param->data = reinterpret_cast<char *>(message);

    message->attr = attr;
    message->src = p_userID;
    message->dst = dst;
    memcpy(message->msg,msg.data(),msg.length());

    bool ret = p_service->sendPackage(proto);
    if(!ret)
    {
        p_error = p_service->error();
        return false;
    }

    return true;
}

void CSMsgProcess::ayncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
}

void CSMsgProcess::ayncSend(const QVariant &data)
{
    Q_UNUSED(data)
}

int CSMsgProcess::unreadCount() const
{
    return 0;
}

int CSMsgProcess::readCount() const
{
    return 0;
}

void CSMsgProcess::setMsgTimeout(int timeout)
{
    p_d->timeout = timeout;
}

int CSMsgProcess::msgTimeout() const
{
    return p_d->timeout;
}
