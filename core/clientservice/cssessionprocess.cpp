#include "cssessionprocess.h"
#include "clientservice.h"
#include "wmp_session.h"


class CSSessionProcessPrivate
{
public:
    CSSessionProcessPrivate(CSSessionProcess *parent)
        :p(parent)
    {}

    void init()
    {
        p->setUniqueID(WMP_PROTO_SESSION_ID);
    }

    quint32 id;
    CSSessionProcess *p;
};

CSSessionProcess::CSSessionProcess(quint32 id,ClientService *parent)
    :AbstractCSProcess(parent)
    ,p_d(new CSSessionProcessPrivate(this))
{
    p_d->init();
    setUserID(id);
}

CSSessionProcess::~CSSessionProcess()
{
    delete p_d;
}

bool CSSessionProcess::syncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
    return true;
}

bool CSSessionProcess::syncSend(const QVariant &data)
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

    quint32 opt = map["opt"].toInt();

    QByteArray message = map["msg"].toByteArray();
    if(message.isEmpty())
        return false;

    /* 2 parameters, user id and user pwd. */
    wm_protocol_t *proto = create_wmp(1);

    proto->base.proto_type = p_service->protoType();
    proto->base.src = p_userID;
    proto->base.dst = CS_SERVICE_ID;
    p_service->localDevice(proto->base.device);

    proto->base.network = p_service->network();
    proto->base.time = p_service->time();

    p_service->protoVersion(proto->base.version);

    wmp_session_t *session = create_wmp_session();

    proto->body.param->main_id = uniqueID();
    proto->body.param->data = reinterpret_cast<char *>(session);

    session->src = p_userID;
    session->dst = dst;
    session->id = opt;

    switch(opt)
    {
    case WMP_SESSION_CET_ID:
    {
        wmp_session_cet_t *cet = create_wmp_session_cet();
        session->param = reinterpret_cast<uint8_t *>(cet);
        cet->attr = attr;
        cet->session_id = map["session_id"].toInt();
        break;
    }
    case WMP_SESSION_DSV_ID:
    {
        wmp_session_dsv_t *dsv = create_wmp_session_dsv();
        session->param = reinterpret_cast<uint8_t *>(dsv);
        dsv->attr = attr;
        dsv->session_id = map["session_id"].toInt();
        break;
    }
    case WMP_SESSION_EXT_ID:
    {
        wmp_session_ext_t *ext = create_wmp_session_ext();
        session->param = reinterpret_cast<uint8_t *>(ext);
        ext->attr = attr;
        ext->session_id = map["session_id"].toInt();
        break;
    }
    case WMP_SESSION_MSG_ID:
    {
        wmp_session_msg_t *msg = create_wmp_session_msg(message.length());
        session->param = reinterpret_cast<uint8_t *>(msg);
        msg->attr = attr;
        msg->session_id = map["session_id"].toInt();
        memcpy(msg,message.data(),message.length());
        break;
    }
    case WMP_SESSION_FLE_ID:
        break;
    case WMP_SESSION_IVT_ID:
    {
        wmp_session_ivt_t *ivt = create_wmp_session_ivt();
        session->param = reinterpret_cast<uint8_t *>(ivt);
        ivt->attr = attr;
        ivt->session_id = map["session_id"].toInt();
        ivt->session_id = map["invite_id"].toInt();
        break;
    }
    default:
        break;
    }

    bool ret = p_service->sendPackage(proto);
    if(!ret)
    {
        p_error = p_service->error();
        return false;
    }

    return true;
}

void CSSessionProcess::ayncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
}

void CSSessionProcess::ayncSend(const QVariant &data)
{
    Q_UNUSED(data)
}
