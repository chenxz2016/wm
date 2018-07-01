#ifndef CSUSERPROCESS_H
#define CSUSERPROCESS_H

#include "abstractcsprocess.h"

class CSUserProcess : public AbstractCSProcess
{
public:
    CSUserProcess(quint32 id,ClientService *parent = 0);
    ~CSUserProcess();

    bool syncRecv(wm_parameter_t *param,quint16 param_num);
    bool syncSend(const QVariant &data);

    void ayncRecv(wm_parameter_t *param,quint16 param_num);
    void ayncSend(const QVariant &data);

    int timeout()const;
    void setTimeout(int timeout);
protected:
    void resend();
protected slots:
	void verifyFriendsNum();
private:
    class CSUserProcessPrivate *p_d;
    friend class CSUserProcessPrivate;
};

#endif // CSUSERPROCESS_H
