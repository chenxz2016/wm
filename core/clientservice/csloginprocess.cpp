#include "clientservice.h"
#include "csloginprocess.h"

#include<wm_protocol.h>
#include<wmp_login.h>
#include<protocol_crypt.h>

static void generate_public_key(uint8_t *pub_key,uint8_t key_len)
{
    qsrand(time(NULL));
    for(uint8_t i=0;i<key_len;i++)
        pub_key[i] = qrand()%255;
}

class CSLoginProcessPrivate
{
public:
    CSLoginProcessPrivate(CSLoginProcess *parent)
        :p(parent)
        ,status(CSLoginProcess::Offline)
        ,timeout(30*1000)
    {}

    void init()
    {
        p->setUniqueID(WMP_PROTO_LOGIN_ID);
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
    wmp_login_t *login = reinterpret_cast<wmp_login_t *>(param->data);
    if(!login)
    {
        /* Parser wmp_login_t failed, push failed to gui. */
        resetPushData();
        appendPushData("res",WM::PacketError);
        emit p_service->startUpdate(p_service);
        return false;
    }

    if(login->user_id!=p_service->userID())
    {
        /* Parser wmp_login_t failed, push failed to gui. */
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
    appendPushData("opt",WM::CSLoginID);
    appendPushData("res",WM::LoginSuccess);
    p_service->setUserID(p_userID);
    emit p_service->startUpdate(p_service);
    return true;
}

/* *************************************************************************
 *
 * @brief:      1. Send public key to request private key.
 *              2. Create a crypted connection to server.
 *
 *
 * ************************************************************************/
bool CSLoginProcess::syncSend(const QVariant &data)
{
    QMap<QString,QVariant> map = data.toMap();
    bool ok = true;

    /* When opt is WMP_PROTO_LOGIN_ID try to create a crypted connection to server. */
    p_userID = map["account"].toString().toInt(&ok);
    if(p_userID<1000)
    {
        p_userID = 0;
        return false;
    }

    p_d->pwd = map["pwd"].toByteArray();
    if(p_d->pwd.isEmpty())
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

    wmp_login_t *login = create_wmp_login();

    proto->head = WMP_HEAD_ID;
    proto->sequence = p_service->protoSequence();
    proto->tail = WMP_TAIL_ID;

    proto->body.param->main_id = WMP_PROTO_LOGIN_ID;
    proto->body.param->data = reinterpret_cast<char *>(login);

    login->attr = 0;
    login->user_id = p_userID;
    login->pwd_len = p_d->pwd.length();
    memcpy(login->password,p_d->pwd.data(),p_d->pwd.length());

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


class CSLoginKeyProcessPrivate
{
public:
    CSLoginKeyProcessPrivate(CSLoginKeyProcess *parent)
		:p(parent)
	{}
	
	void init()
    {
        p->setUniqueID(WMP_PROTO_LOGIN_KEY_ID);

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
    }
	
	WMEncryptKey pubKey;
	WMEncryptKey priKey;
	int timeout;
    int timerID;
    QByteArray pwd;
	CSLoginKeyProcess *p;
};

CSLoginKeyProcess::CSLoginKeyProcess(ClientService *parent)
    :AbstractCSProcess(parent)
    ,p_d(new CSLoginKeyProcessPrivate(this))
{
	p_d->init();
}

CSLoginKeyProcess::~CSLoginKeyProcess()
{
	delete p_d;
}

bool CSLoginKeyProcess::syncRecv(wm_parameter_t *param,quint16 param_num)
{
    if(param_num!=1)
        return false;

    if(!param->data)
        return false;

	wmp_login_key_t *key = reinterpret_cast<wmp_login_key_t *>(param->data);
	if(!key)
		return false;

	if(key->user_id!=p_userID)
		return false;

    p_service->setUserID(p_userID);
	/* Update key. */
	WMEncryptKey k;
	k.setKey(key->key_len,(char *)key->key,key->type);
	p_service->setEncryptKey(k);

	/* push key request successfully to gui. */
	resetPushData();
	appendPushData("res",WM::KeyReqSuccess);
	emit p_service->startUpdate(p_service);
	
    /* start to login to server. */
    QMap<QString,QVariant> map;
    map["account"] = p_userID;
    map["opt"] = WMP_PROTO_LOGIN_ID;
    map["pwd"] = p_d->pwd;
    p_service->flush(map);

	return true;
}

bool CSLoginKeyProcess::syncSend(const QVariant &data)
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

	/* 1 parameters, user id and user pwd. */
    wm_protocol_t *proto = create_wmp(1);

	proto->head = WMP_HEAD_ID;
	proto->sequence = p_service->protoSequence();
	proto->tail = WMP_TAIL_ID;


	proto->base.proto_type = p_service->protoType();
	proto->base.src = p_userID;
	proto->base.dst = CS_SERVICE_ID;
	p_service->localDevice(proto->base.device);

	proto->base.network = p_service->network();
	proto->base.time = p_service->time();

	p_service->protoVersion(proto->base.version);

    wmp_login_key_t *key = create_wmp_login_key();

	proto->body.param->main_id = WMP_PROTO_LOGIN_KEY_ID;
	proto->body.param->data = reinterpret_cast<char *>(key);

	key->attr = 0;
	key->user_id = p_userID;
	key->type = WMP_LOGIN_KEY_PUBLIC;
	key->key_len = WMP_KEY_LENGTH;
	generate_public_key(key->key,key->key_len);

	bool ret = p_service->sendPackage(proto);
	if(!ret)
	{
		return false;
	}
	
	p_d->timerID = startTimer(p_d->timeout);
	return true;
}

void CSLoginKeyProcess::ayncRecv(wm_parameter_t *param,quint16 param_num)
{
	Q_UNUSED(param)
    Q_UNUSED(param_num)
}

void CSLoginKeyProcess::ayncSend(const QVariant &data)
{
    Q_UNUSED(data)
}

void CSLoginKeyProcess::setTimeout(int timeout)
{
	p_d->timeout = timeout;
}

int CSLoginKeyProcess::timeout()const
{
	return p_d->timeout;
}

WMEncryptKey CSLoginKeyProcess::publicKey()const
{
    return p_d->pubKey;
}

WMEncryptKey CSLoginKeyProcess::privateKey()const
{
    return p_d->priKey;
}

void CSLoginKeyProcess::timerEvent(QTimerEvent *event)
{
	QObject::timerEvent(event);
}
