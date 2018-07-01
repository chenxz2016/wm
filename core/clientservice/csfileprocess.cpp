#include "clientservice.h"
#include "csfileprocess.h"

#include <QFileInfo>
#include <QDateTime>
#include <QMap>
#include <qglobal.h>
#include <wmp_file.h>


struct CSFileInfo
{
    CSFileInfo():flag(0),offset(0){}
    CSFileInfo(const CSFileInfo &fi)
    {
        fileName = fi.fileName;
        recvDT = fi.recvDT;
        sender = fi.sender;
        recver = fi.recver;
        flag = fi.flag;
        percent = fi.percent;
        offset = fi.offset;
        status = fi.status;
    }

    CSFileInfo &operator=(const CSFileInfo &fi)
    {
        fileName = fi.fileName;
        recvDT = fi.recvDT;
        sender = fi.sender;
        recver = fi.recver;
        flag = fi.flag;
        percent = fi.percent;
        offset = fi.offset;
        status = fi.status;
        return *this;
    }


    QString fileName;
    QDateTime recvDT;
    quint32 sender;
    quint32 recver;

    QFile file;
    quint8 flag;
    float percent;
    quint64 offset;
    CSFileProcess::CSFileStatus status;
};

class CSFileProcessPrivate
{
public:
    CSFileProcessPrivate(CSFileProcess *parent)
        :p(parent)
        ,packSize(12*1024)
        ,interval(1000*10)
    {}

    void init()
    {
        p->setUniqueID(WMP_PROTO_FILE_ID);
    }

    CSFileProcess *p;

    int packSize;
    int interval;

    QMap<QString,CSFileInfo> recvFileMap;
    QMap<QString,CSFileInfo> sendFileMap;

    QMap<quint32,CSFileInfo> recvingFile;
    QMap<quint32,CSFileInfo> sendingFile;
};

CSFileProcess::CSFileProcess(quint32 id,ClientService *service)
    :AbstractCSProcess(service)
    ,p_d(new CSFileProcessPrivate(this))
{
    p_d->init();
	setUserID(id);
}

CSFileProcess::~CSFileProcess()
{
    delete p_d;
}

int CSFileProcess::filePacketSize() const
{
    return p_d->packSize;
}

void CSFileProcess::setFilePacketSize(int size)
{
    p_d->packSize = size;
}

bool CSFileProcess::syncRecv(wm_parameter_t *param, quint16 param_num)
{
    if(!param_num)
        return true;

    for(quint16 i = 0;i<param_num;i++)
    {
        wmp_file_t *file = reinterpret_cast<wmp_file_t *>(param[i].data);
        if(!file)
            continue ;

        CSFileInfo &fi = p_d->recvingFile[file->unique];
        if(file->attr)
        {
            fi.fileName = QString((char *)file->data);
            fi.flag = 1;
            if(fi.file.open(QIODevice::ReadWrite))
            {
                p_error = fi.file.errorString();
                return false;
            }
            if(p_d->recvingFile.count()==1)
                ;//timerID = startTimer(interval);
        }
        else
        {
            if(!fi.flag)
            {
                fi.file.write((char *)file->data,file->data_len);
                fi.percent = (double)fi.file.size()/file->block;
            }
        }
    }
    return true;
}

bool CSFileProcess::syncSend(const QVariant &data)
{
    CSFileInfo fi;
    fi.fileName = data.toString();
    p_d->sendingFile[p_d->sendingFile.count()] = fi;
    return true;
}

void CSFileProcess::ayncRecv(wm_parameter_t *param, quint16 param_num)
{
    Q_UNUSED(param)
    Q_UNUSED(param_num)
}

void CSFileProcess::ayncSend(const QVariant &data)
{
    Q_UNUSED(data)
}

int CSFileProcess::checkFileStatus(const QString &fileName)
{
    QMap<quint32,CSFileInfo>::Iterator i = p_d->recvingFile.begin();
    for(;i!=p_d->recvingFile.end();i++)
    {
        CSFileInfo &fi = i.value();
        if(fi.fileName == fileName)
            return fi.status;
    }

    i = p_d->sendingFile.begin();
    for(;i!=p_d->sendingFile.end();i++)
    {
        CSFileInfo &fi = i.value();
        if(fi.fileName == fileName)
            return fi.status;
    }

    return None;
}

void CSFileProcess::removeFile(const QString &fileName)
{
    p_d->recvFileMap.remove(fileName);
    p_d->sendFileMap.remove(fileName);
}

float CSFileProcess::recvPercent(const QString &fileName)
{
    QMap<quint32,CSFileInfo>::Iterator i = p_d->recvingFile.begin();
    for(;i!=p_d->recvingFile.end();i++)
    {
        CSFileInfo &fi = i.value();
        if(fi.fileName == fileName)
            return fi.percent;
    }
    return 0;
}

float CSFileProcess::sendPercent(const QString &fileName)
{
    QMap<quint32,CSFileInfo>::Iterator i = p_d->sendingFile.begin();
    for(;i!=p_d->sendingFile.end();i++)
    {
        CSFileInfo &fi = i.value();
        if(fi.fileName == fileName)
            return fi.percent;
    }
    return 0;
}

void CSFileProcess::timerEvent(QTimerEvent *event)
{
    QMap<quint32,CSFileInfo>::Iterator i = p_d->sendingFile.begin();
    for(;i!=p_d->sendingFile.end();i++)
    {
        CSFileInfo &fi = i.value();
        if(!fi.file.isOpen())
        {
            if(!fi.file.open(QIODevice::ReadOnly))
            {
                p_d->sendingFile.erase(i++);
                if(!p_d->sendingFile.count())
                    ;//killTimer(timerID);

                emit error(1,fi.fileName);
            }
        }

        QByteArray d = fi.file.read(p_d->packSize);
        fi.offset += d.size();

        if(p_service)
        {
            if(p_service->sendData(d))
                emit error(1,p_service->error());
        }
    }

    QObject::timerEvent(event);
}


