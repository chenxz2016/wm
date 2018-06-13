#include "csbeatheartprocess.h"
#include "wmp_beat_heart.h"
#include "clientservice.h"

#include <QTimer>

class CSBeatHeartProcessPrivate
{
public:
    CSBeatHeartProcessPrivate(CSBeatHeartProcess *parent)
        :p(parent)
		,count(0)
		,timeout(60)
		,req(false)
		,invalidCount(0)
    {}

    void init()
    {
        p->setUniqueID(WMP_PROTO_BH_ID);
    }
	
	CSBeatHeartProcess *p;
	quint32 count;
	int timeout;
	bool req;
	bool active;
	quint32 invalidCount;
};

CSBeatHeartProcess::CSBeatHeartProcess(quint32 id,ClientService *service)
    :AbstractCSProcess(service)
    ,p_d(new CSBeatHeartProcessPrivate(this))
{
    p_d->init();
	setUserID(id);
}

CSBeatHeartProcess::~CSBeatHeartProcess()
{
    delete p_d;
}

bool CSBeatHeartProcess::syncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param_num)
	
    wmp_beat_heart_t *bh = reinterpret_cast<wmp_beat_heart_t *>(param->data);
	if(!bh)
		return false;
	
	p_d->req = false;
	
    return true;
}

bool CSBeatHeartProcess::syncSend(const QVariant &data)
{
	Q_UNUSED(data);

    /* 2 parameters, user id and user pwd. */
    wm_protocol_t *proto = allocate_wmp(1);

    proto->base.proto_type = p_service->protoType();
    proto->base.src = p_userID;
    proto->base.dst = CS_SERVICE_ID;
    p_service->localDevice(proto->base.device);

    proto->base.network = p_service->network();
    proto->base.time = p_service->time();

    p_service->protoVersion(proto->base.version);

    wmp_beat_heart_t *bh = allocate_wmp_beat_heart();

    proto->body.param->main_id = uniqueID();
    proto->body.param->data = reinterpret_cast<char *>(bh);

    WMP_BeatHeartSetCTS(bh);
    WMP_BeatHeartSetUserID(bh,p_userID);
	WMP_BeatHeartSetFlag(bh,WMP_BEAT_HEART_REQ);

    return p_service->sendPackage(proto);
}

void CSBeatHeartProcess::ayncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
}

void CSBeatHeartProcess::ayncSend(const QVariant &data)
{
	Q_UNUSED(data);
	
    /* 2 parameters, user id and user pwd. */
    wm_protocol_t *proto = allocate_wmp(1);

    proto->base.proto_type = p_service->protoType();
    proto->base.src = p_userID;
    proto->base.dst = CS_SERVICE_ID;
    p_service->localDevice(proto->base.device);

    proto->base.network = p_service->network();
    proto->base.time = p_service->time();

    p_service->protoVersion(proto->base.version);

    wmp_beat_heart_t *bh = allocate_wmp_beat_heart();

    proto->body.param->main_id = WMP_PROTO_BH_ID;
    proto->body.param->data = reinterpret_cast<char *>(bh);

    WMP_BeatHeartSetCTS(bh);
    WMP_BeatHeartSetUserID(bh,p_userID);
	WMP_BeatHeartSetFlag(bh,WMP_BEAT_HEART_REQ);

    bool ret = p_service->sendPackage(proto);
	if(!ret)
        emit error(1,"Send package failed.");
}

void CSBeatHeartProcess::setTimeout(int timeout)
{
	p_d->timeout = timeout;
	startTimer(p_d->timeout);
}

int CSBeatHeartProcess::timeout()const
{
	return p_d->timeout;
}

void CSBeatHeartProcess::setActive(bool active)
{
	p_d->active = active;
}

bool CSBeatHeartProcess::active()const
{
	return p_d->active;
}

void CSBeatHeartProcess::reset()
{
	p_d->count = 0;
	p_d->invalidCount = 0;
	p_d->req = false;
}

void CSBeatHeartProcess::timerEvent(QTimerEvent *event)
{
	if(!p_d->active)
		return ;
	
	QVariant data;
	bool ret = syncSend(data);
	if(ret)
	{
		p_d->req = true;
        QTimer::singleShot(5000,this,SLOT(checkRsp()));
	}

	AbstractCSProcess::timerEvent(event);
}

void CSBeatHeartProcess::checkRsp()
{
	if(p_d->req)
		p_d->invalidCount++;
	
	if(p_d->invalidCount>5)
	{
		setActive(false);
        emit error(1,tr("Beat Heart Timeout."));
	}
}
