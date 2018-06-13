#ifndef CSSESSIONPROCESS_H
#define CSSESSIONPROCESS_H

#include "abstractcsprocess.h"

class CSSessionProcess : public AbstractCSProcess
{
public:
    CSSessionProcess(quint32 id,ClientService *parent = 0);
    ~CSSessionProcess();

    bool syncRecv(wm_parameter_t *param,quint16 param_num);
    bool syncSend(const QVariant &data);

    void ayncRecv(wm_parameter_t *param,quint16 param_num);
    void ayncSend(const QVariant &data);
private:
    class CSSessionProcessPrivate *p_d;
    friend class CSSessionProcessPrivate;
};

#endif // CSSESSIONPROCESS_H
