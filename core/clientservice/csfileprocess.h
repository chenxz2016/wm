#ifndef CSFILEPROCESS_H
#define CSFILEPROCESS_H

#include "abstractcsprocess.h"


class CSFileProcess : public AbstractCSProcess
{
    Q_OBJECT
    Q_PROPERTY(int filePacketSize READ filePacketSize WRITE setFilePacketSize)
public:
    enum CSFileStatus
    {
        None,
        Sending,
        Recving
    };

    CSFileProcess(quint32 id,ClientService *service = 0);
    ~CSFileProcess();

    int filePacketSize()const;
    void setFilePacketSize(int size);

    bool syncRecv(wm_parameter_t *param,quint16 param_num);
    bool syncSend(const QVariant &data);

    void ayncRecv(wm_parameter_t *param,quint16 param_num);
    void ayncSend(const QVariant &data);

    int checkFileStatus(const QString &fileName);

    void removeFile(const QString &fileName);

    float recvPercent(const QString &fileName);
    float sendPercent(const QString &fileName);
protected:
    void timerEvent(QTimerEvent *event);
private:
    class CSFileProcessPrivate *p_d;
    friend class CSFileProcessPrivate;
};

#endif // CSFILEPROCESS_H
