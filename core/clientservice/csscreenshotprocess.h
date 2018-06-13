#ifndef CSSCREENSHOTPROCESS_H_
#define CSSCREENSHOTPROCESS_H_

#include "abstractcsprocess.h"

class CSScreenShotProcess : public AbstractCSProcess
{
	Q_OBJECT
public:
    CSScreenShotProcess(quint32 id,ClientService *parent = 0);
    ~CSScreenShotProcess();

    bool syncRecv(wm_parameter_t *param,quint16 param_num);
    bool syncSend(const QVariant &data);

    void ayncRecv(wm_parameter_t *param,quint16 param_num);
    void ayncSend(const QVariant &data);

    int photoTimeout()const;
    void setPhotoTimeout(int timeout);

    int recvPhotoCount()const;
    int sendPhotoCount()const;
private:
    class CSScreenShotProcessPrivate *p_d;
    friend class CSScreenShotProcessPrivate;
};


#endif // CSSCREENSHOTPROCESS_H_
