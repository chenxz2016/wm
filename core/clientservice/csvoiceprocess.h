#ifndef CSVOICEPROCESS_H
#define CSVOICEPROCESS_H

#include "abstractcsprocess.h"

class CSVoiceProcess : public AbstractCSProcess
{
    Q_OBJECT
public:
    CSVoiceProcess(quint32 id,ClientService *parent = 0);
    ~CSVoiceProcess();

    bool syncRecv(wm_parameter_t *param,quint16 param_num);
    bool syncSend(const QVariant &data);

    void ayncRecv(wm_parameter_t *param,quint16 param_num);
    void ayncSend(const QVariant &data);

    void startVoiceCall(quint32 dst);
    void stopVoiceCall(quint32 dst);

    void setVoiceTimeout(int timeout);
    int voiceTimeout()const;
private:
    class CSVoiceProcessPrivate *p_d;
    friend class CSVoiceProcessPrivate;
};

#endif // CSVOICEPROCESS_H
