#include "csuserprocess.h"
#include "clientservice.h"
#include "wmp_user.h"


class CSUserProcessPrivate
{
public:
    CSUserProcessPrivate(CSUserProcess *parent)
        :p(parent)
    {}

    void init()
    {
        p->setUniqueID(WMP_PROTO_USER_ID);
    }

    int timeout;
    CSUserProcess *p;
};

CSUserProcess::CSUserProcess(quint32 id,ClientService *parent)
    :AbstractCSProcess(parent)
    ,p_d(new CSUserProcessPrivate(this))
{
    p_d->init();
    setUserID(id);
}

CSUserProcess::~CSUserProcess()
{
    delete p_d;
}

bool CSUserProcess::syncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
    return true;
}

bool CSUserProcess::syncSend(const QVariant &data)
{
    QMap<QString,QVariant> map = data.toMap();
    bool ok = true;
    quint32 id = map["dst"].toInt();
    switch(id)
    {
    case WMP_USER_ADD_ID:
        break;
    case WMP_USER_DEL_ID:
        break;
    case WMP_USER_SET_ID:
        break;
    case WMP_USER_MSG_ID:
        break;
    case WMP_USER_FRIEND_ID:
        break;
    default:
        break;
    }
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
    wm_protocol_t *proto = allocate_wmp(1);

    proto->base.proto_type = p_service->protoType();
    proto->base.src = p_userID;
    proto->base.dst = CS_SERVICE_ID;
    p_service->localDevice(proto->base.device);

    proto->base.network = p_service->network();
    proto->base.time = p_service->time();

    p_service->protoVersion(proto->base.version);

    wmp_user_t *user = allocate_wmp_user();

    proto->body.param->main_id = uniqueID();
    proto->body.param->data = reinterpret_cast<char *>(user);

    user->src = p_userID;
    user->dst = dst;
    user->id = opt;

    switch(opt)
    {
    case WMP_USER_ADD_ID:
    {
        wmp_user_add_t *add = allocate_wmp_user_add();
        user->param = reinterpret_cast<uint8_t *>(add);
        add->attr = map["attr"].toInt();
        add->msg_len = message.length();
        memcpy(add->msg,message.data(),add->msg_len);
        break;
    }
    case WMP_USER_DEL_ID:
    {
        wmp_user_del_t *del = allocate_wmp_user_del();
        user->param = reinterpret_cast<uint8_t *>(del);
        del->attr = map["attr"].toInt();
        del->id = map["id"].toInt();
        break;
    }
    case WMP_USER_SET_ID:
    {
        QList<QVariant> list = map["list"].toList();
        wmp_user_set_t *set = allocate_wmp_user_set(list.count());
        user->param = reinterpret_cast<uint8_t *>(set);
        set->attr = map["attr"].toInt();
        for(uint16_t i = 0;i<set->property_num;i++)
        {
            QMap<QString,QVariant> m = list.at(i).toMap();
            QByteArray d = m["data"].toByteArray();
            set->property_list[i].id = m["id"].toInt();
            set->property_list[i].type = m["type"].toInt();
            set->property_list[i].len = d.length();
            memcpy(set->property_list[i].data,d.data(),d.length());
        }
        break;
    }
    case WMP_USER_MSG_ID:
    {
        wmp_user_msg_t *msg = allocate_wmp_user_msg(message.length());
        user->param = reinterpret_cast<uint8_t *>(msg);
        msg->attr = map["attr"].toInt();
        memcpy(msg->msg,message.data(),message.length());
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

void CSUserProcess::ayncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
}

void CSUserProcess::ayncSend(const QVariant &data)
{
    Q_UNUSED(data)
}

int CSUserProcess::timeout() const
{
    return p_d->timeout;
}

void CSUserProcess::setTimeout(int timeout)
{
    p_d->timeout = timeout;
}
