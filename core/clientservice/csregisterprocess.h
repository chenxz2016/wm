#ifndef CSREGISTERPROCESS_H
#define CSREGISTERPROCESS_H

#include "abstractcsprocess.h"


class CSRegisterProcess : public AbstractCSProcess
{
public:
    CSRegisterProcess(ClientService *parent = 0);
    ~CSRegisterProcess();

    bool syncRecv(wm_parameter_t *param,quint16 param_num);
    bool syncSend(const QVariant &data);

    void ayncRecv(wm_parameter_t *param,quint16 param_num);
    void ayncSend(const QVariant &data);
private:
    class CSRegisterProcessPrivate *p_d;
    friend class CSRegisterProcessPrivate;
};

#endif // CSREGISTERPROCESS_H
