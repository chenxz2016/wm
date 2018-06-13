#ifndef CSMSGPROCESS_H_
#define CSMSGPROCESS_H_

#include "abstractcsprocess.h"
#include <wm_protocol.h>


class CSMsgProcess : public AbstractCSProcess
{
    Q_OBJECT
    Q_PROPERTY(int msgTimeout READ msgTimeout WRITE setMsgTimeout)
public:
    CSMsgProcess(quint32 id,ClientService *parent = 0);
    ~CSMsgProcess();

    bool syncRecv(wm_parameter_t *param,quint16 param_num);
    bool syncSend(const QVariant &data);

    void ayncRecv(wm_parameter_t *param,quint16 param_num);
    void ayncSend(const QVariant &data);

    int unreadCount()const;
    int readCount()const;
	
	void setMsgTimeout(int timeout);
	int msgTimeout()const;
private:
    class CSMsgProcessPrivate *p_d;
    friend class CSMsgProcessPrivate;
};


#endif //CSMSGPROCESS_H_
