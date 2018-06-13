#ifndef CSBEATHEARTPROCESS_H
#define CSBEATHEARTPROCESS_H

#include "abstractcsprocess.h"


class CSBeatHeartProcess : public AbstractCSProcess
{
public:
    CSBeatHeartProcess(quint32 id,ClientService *service = 0);
    ~CSBeatHeartProcess();

    bool syncRecv(wm_parameter_t *param,quint16 param_num);
    bool syncSend(const QVariant &data);

    void ayncRecv(wm_parameter_t *param,quint16 param_num);
    void ayncSend(const QVariant &data);

	void setTimeout(int timeout);
	int timeout()const;
	
	void setActive(bool active);
	bool active()const;
	
	void reset();
protected:
	void timerEvent(QTimerEvent *event);
	
private slots:
	void checkRsp();
private:
    class CSBeatHeartProcessPrivate *p_d;
    friend class CSBeatHeartProcessPrivate;
};

#endif // CSBEATHEARTPROCESS_H
