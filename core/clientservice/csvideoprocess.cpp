#include "csvideoprocess.h"
#include "clientservice.h"
#include "wmp_video.h"

class CSVideoProcessPrivate
{
public:
    CSVideoProcessPrivate(CSVideoProcess *parent)
        :p(parent)
        ,timeout(5000)
    {}

    void init()
    {
        p->setUniqueID(WMP_PROTO_VIDEO_ID);
    }

    CSVideoProcess *p;
    int timeout;
};

CSVideoProcess::CSVideoProcess(quint32 id,ClientService *parent)
    :AbstractCSProcess(parent)
    ,p_d(new CSVideoProcessPrivate(this))
{
    p_d->init();
    setUserID(id);
}

CSVideoProcess::~CSVideoProcess()
{
    delete p_d;
}

bool CSVideoProcess::syncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
    return true;
}

bool CSVideoProcess::syncSend(const QVariant &data)
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

    wmp_video_t *video = allocate_wmp_video(stream.length());

    proto->body.param->main_id = uniqueID();
    proto->body.param->data = reinterpret_cast<char *>(video);

    video->src = p_userID;
    video->dst = dst;
    video->src = p_userID;
    memcpy(video->video,stream.data(),stream.length());

    bool ret = p_service->sendPackage(proto);
    if(!ret)
    {
        p_error = p_service->error();
        return false;
    }

    return true;
}

void CSVideoProcess::ayncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
}

void CSVideoProcess::ayncSend(const QVariant &data)
{
    Q_UNUSED(data)
}

void CSVideoProcess::startVideoCall(quint32 dst)
{
    Q_UNUSED(dst)
}

void CSVideoProcess::stopVideoCall(quint32 dst)
{
    Q_UNUSED(dst)
}

int CSVideoProcess::videoTimeout() const
{
    return p_d->timeout;
}

void CSVideoProcess::setVideoTimeout(int timeout)
{
    p_d->timeout = timeout;
}
