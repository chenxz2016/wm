#include "csregisterprocess.h"


class CSRegisterProcessPrivate
{
public:
    CSRegisterProcessPrivate(CSRegisterProcess *parent)
        :p(parent)
    {}

    void init()
    {
        p->setUniqueID(WMP_PROTO_REGISTER_ID);
    }

    CSRegisterProcess *p;
};

CSRegisterProcess::CSRegisterProcess(ClientService *parent)
    :AbstractCSProcess(parent)
    ,p_d(new CSRegisterProcessPrivate(this))
{
    p_d->init();
}

CSRegisterProcess::~CSRegisterProcess()
{
    delete p_d;
}

bool CSRegisterProcess::syncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
    return true;
}

bool CSRegisterProcess::syncSend(const QVariant &data)
{
    Q_UNUSED(data)
    return true;
}

void CSRegisterProcess::ayncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
}

void CSRegisterProcess::ayncSend(const QVariant &data)
{
    Q_UNUSED(data)
}
