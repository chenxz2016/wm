#include "csscreenshotprocess.h"

class CSScreenShotProcessPrivate
{
public:
    CSScreenShotProcessPrivate(quint32 user_id,CSScreenShotProcess *parent)
        :id(user_id)
        ,p(parent)
    {}

    void init()
    {
        p->setUniqueID(WMP_PROTO_MSG_ID);
    }

    int timeout;
    quint32 id;
    CSScreenShotProcess *p;
};

CSScreenShotProcess::CSScreenShotProcess(quint32 id, ClientService *parent)
    :AbstractCSProcess(parent)
    ,p_d(new CSScreenShotProcessPrivate(id,this))
{
    p_d->init();
    setUserID(id);
}

CSScreenShotProcess::~CSScreenShotProcess()
{
    delete p_d;
}

bool CSScreenShotProcess::syncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
    return true;
}

bool CSScreenShotProcess::syncSend(const QVariant &data)
{
    Q_UNUSED(data)
    return true;
}

void CSScreenShotProcess::ayncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
}

void CSScreenShotProcess::ayncSend(const QVariant &data)
{
    Q_UNUSED(data)
}

int CSScreenShotProcess::photoTimeout() const
{
    return p_d->timeout;
}

void CSScreenShotProcess::setPhotoTimeout(int timeout)
{
    p_d->timeout = timeout;
}

int CSScreenShotProcess::recvPhotoCount() const
{
    return 0;
}

int CSScreenShotProcess::sendPhotoCount() const
{
    return 0;
}


