#include "csvoiceprocess.h"

#include "clientservice.h"
#include "wmp_sound.h"

class CSVoiceProcessPrivate
{
public:
    CSVoiceProcessPrivate(CSVoiceProcess *parent)
        :p(parent)
        ,timeout(5000)
    {}

    void init()
    {
        p->setUniqueID(WMP_PROTO_SOUND_ID);
    }

    int timeout;
    CSVoiceProcess *p;
};

CSVoiceProcess::CSVoiceProcess(quint32 id,ClientService *parent)
    :AbstractCSProcess(parent)
    ,p_d(new CSVoiceProcessPrivate(this))
{
    p_d->init();
    setUserID(id);
}

CSVoiceProcess::~CSVoiceProcess()
{
    delete p_d;
}

bool CSVoiceProcess::syncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
    return true;
}

bool CSVoiceProcess::syncSend(const QVariant &data)
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

    QByteArray stream = map["stream"].toByteArray();
    if(stream.isEmpty())
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

    wmp_sound_t *sound = allocate_wmp_sound(stream.length());

    proto->body.param->main_id = uniqueID();
    proto->body.param->data = reinterpret_cast<char *>(sound);

    sound->src = p_userID;
    sound->dst = dst;
    sound->src = p_userID;
    memcpy(sound->sound,stream.data(),stream.length());

    bool ret = p_service->sendPackage(proto);
    if(!ret)
    {
        p_error = p_service->error();
        return false;
    }

    return true;
}

void CSVoiceProcess::ayncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
}

void CSVoiceProcess::ayncSend(const QVariant &data)
{
    Q_UNUSED(data)
}

void CSVoiceProcess::startVoiceCall(quint32 dst)
{
    Q_UNUSED(dst)
}

void CSVoiceProcess::stopVoiceCall(quint32 dst)
{
    Q_UNUSED(dst)
}

void CSVoiceProcess::setVoiceTimeout(int timeout)
{
    p_d->timeout = timeout;
}

int CSVoiceProcess::voiceTimeout() const
{
    return p_d->timeout;
}
