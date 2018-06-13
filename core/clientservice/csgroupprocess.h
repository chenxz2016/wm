#ifndef CSGROUPPROCESS_H
#define CSGROUPPROCESS_H

#include "abstractcsprocess.h"

class CSGroupProcess : public AbstractCSProcess
{
public:
    CSGroupProcess(quint32 id,ClientService *service = 0);
    ~CSGroupProcess();

    bool syncRecv(wm_parameter_t *param,quint16 param_num);
    bool syncSend(const QVariant &data);

    void ayncRecv(wm_parameter_t *param,quint16 param_num);
    void ayncSend(const QVariant &data);
private:
    class CSGroupProcessPrivate *p_d;
    friend class CSGroupProcessPrivate;
};

#endif // CSGROUPPROCESS_H
