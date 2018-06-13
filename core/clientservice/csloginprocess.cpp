#include "clientservice.h"
#include "csloginprocess.h"

#include<wm_protocol.h>
#include<wmp_login.h>
#include<protocol_crypt.h>

class CSLoginProcessPrivate
{
public:
    CSLoginProcessPrivate(CSLoginProcess *parent)
        :p(parent)
        ,status(CSLoginProcess::Offline)
    {}

    void init()
    {
        p->setUniqueID(WMP_PROTO_LOGIN_ID);

        int ret = protocol_crypt_init(0);
        if(ret!=P_CRYPT_SUCCESS)
        {
            return ;
        }
        WMEncryptKey key;
        key.key_len = 255;
        ret = generate_cbc_key((unsigned char *)key.key,key.key_len);;
        if(ret!=P_CRYPT_SUCCESS)
        {
            return ;
        }
        p->setEnryptKey(key);
    }

    QByteArray pwd;
    CSLoginProcess::CSLoginStatus status;
    int timeout;
    int timerID;

    char loginDevice[24];
    quint16 proto_type;
    char protoVersion[10];

    QString error;
    CSLoginProcess *p;
};

CSLoginProcess::CSLoginProcess(ClientService *parent)
    :AbstractCSProcess(parent)
    ,p_d(new CSLoginProcessPrivate(this))
{
    p_d->init();
}

CSLoginProcess::~CSLoginProcess()
{
    delete p_d;
}

bool CSLoginProcess::syncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param_num)
    if(param->main_id==WMP_PROTO_LOGIN_KEY_ID)
    {
        wmp_login_key_t *key = reinterpret_cast<wmp_login_key_t *>(param->data);
        if(!key)
            return false;

        if(key->user_id!=p_userID)
            return false;

        WMEncryptKey k;
        k.setKey(key->key_len,(char *)key->key,key->type);
        p_service->setEncryptKey(k);

        QMap<QString,QVariant> map;
        map["account"] = p_userID;
        map["pwd"] = p_d->pwd;
        syncSend(map);

        resetPushData();
        appendPushData("res",WM::KeyReqSuccess);
        emit p_service->startUpdate(p_service);
    }
    else if(param->main_id==WMP_PROTO_LOGIN_ID)
    {
        wmp_login_t *login = reinterpret_cast<wmp_login_t *>(param->data);
        if(!login)
        {
            resetPushData();
            appendPushData("res",WM::PacketError);
            emit p_service->startUpdate(p_service);
            return false;
        }

        if(login->user_id!=p_userID)
        {
            resetPushData();
            appendPushData("res",WM::IDError);
            emit p_service->startUpdate(p_service);
            return false;
        }

        if(login->result!=WMP_LOGIN_RESULT_SUCCESS)
        {
            resetPushData();
            appendPushData("res",login->result);
            emit p_service->startUpdate(p_service);
            return false;
        }

        resetPushData();
        appendPushData("res",WM::LoginSuccess);
        emit p_service->startUpdate(p_service);
    }

    return true;
}

bool CSLoginProcess::syncSend(const QVariant &data)
{
    QMap<QString,QVariant> map = data.toMap();
    bool ok = true;
    p_userID = map["account"].toString().toInt(&ok);
    if(p_userID<1000)
    {
        p_userID = 0;
        return false;
    }

    p_d->pwd = map["pwd"].toByteArray();
    if(p_d->pwd.isEmpty())
        return false;

    quint8 type = map["type"].toInt();
    if(!type)
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

    wmp_login_key_t *key = allocate_wmp_login_key();

    proto->body.param->main_id = WMP_PROTO_LOGIN_KEY_ID;
    proto->body.param->data = reinterpret_cast<char *>(key);

    key->type = type;
    key->attr = 1;
    key->user_id = p_userID;

    bool ret = p_service->sendPackage(proto);
    if(!ret)
    {
        return false;
    }

    p_d->timerID = startTimer(p_d->timeout);
    return true;
}

void CSLoginProcess::ayncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
}

void CSLoginProcess::ayncSend(const QVariant &data)
{
    Q_UNUSED(data)
}

CSLoginProcess::CSLoginStatus CSLoginProcess::loginStatus() const
{
    return p_d->status;
}

void CSLoginProcess::setLoginStatus(CSLoginProcess::CSLoginStatus status)
{
    p_d->status = status;
}

void CSLoginProcess::setLoginTimeout(int timeout)
{
    p_d->timeout = timeout;
}

int CSLoginProcess::loginTimeout() const
{
    return p_d->timeout;
}

void CSLoginProcess::timerEvent(QTimerEvent *event)
{
    if(p_d->status==Offline)
    {
        resetPushData();
        appendPushData("res",WM::Timeout);
        emit p_service->startUpdate(p_service);
        killTimer(p_d->timerID);
    }
    AbstractCSProcess::timerEvent(event);
}

void CSLoginProcess::setEnryptKey(const WMEncryptKey &key)
{
    p_service->setEncryptKey(key);
}

