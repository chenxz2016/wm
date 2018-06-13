#ifndef CSVIDEOPROCESS_H
#define CSVIDEOPROCESS_H

#include "abstractcsprocess.h"

class CSVideoProcess : public AbstractCSProcess
{
public:
    CSVideoProcess(quint32 id,ClientService *parent = 0);
    ~CSVideoProcess();

    bool syncRecv(wm_parameter_t *param,quint16 param_num);
    bool syncSend(const QVariant &data);

    void ayncRecv(wm_parameter_t *param,quint16 param_num);
    void ayncSend(const QVariant &data);

    void startVideoCall(quint32 dst);
    void stopVideoCall(quint32 dst);

    int videoTimeout()const;
    void setVideoTimeout(int timeout);
private:
    class CSVideoProcessPrivate *p_d;
    friend class CSVideoProcessPrivate;
};

#endif // CSVIDEOPROCESS_H
