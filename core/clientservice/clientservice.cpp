#include "clientservice.h"
#include "csfileprocess.h"
#include "csgroupprocess.h"
#include "csloginprocess.h"
#include "csmsgprocess.h"
#include "csscreenshotprocess.h"
#include "cssessionprocess.h"
#include "csuserprocess.h"
#include "csvideoprocess.h"
#include "csvoiceprocess.h"

#include <QTcpSocket>
#include <wmp_login.h>
#include <wmp_beat_heart.h>
#include <wmp_file.h>
#include <wmp_group.h>
#include <wmp_message.h>
#include <wmp_register.h>
#include <wmp_session.h>
#include <wmp_sound.h>
#include <wmp_user.h>
#include <wmp_video.h>
#include <wm_protocol.h>
#include <protocol_package.h>
#include <protocol_crypt.h>
#include <crc32.h>
#include <QDateTime>

#include<Winsock2.h>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")

#define WM_HOST_FAKE    "192.168.0.110"
#define WM_PORT_FAKE    3710



class ClientServicePrivate
{
public:
    ClientServicePrivate(ClientService *parent)
        :p(parent)
        ,sequence(0)
    {
        tcp = new QTcpSocket(p);
    }

    void init()
    {
        AbstractCSProcess *process = new CSFileProcess(id,p);
        pm[process->uniqueID()] = process;

        process = new CSLoginProcess(p);
        pm[process->uniqueID()] = process;

        process = new CSLoginKeyProcess(p);
        pm[process->uniqueID()] = process;

        process = new CSMsgProcess(id,p);
        pm[process->uniqueID()] = process;

        process = new CSScreenShotProcess(id,p);
        pm[process->uniqueID()] = process;

        process = new CSUserProcess(id,p);
        pm[process->uniqueID()] = process;

        process = new CSGroupProcess(id,p);
        pm[process->uniqueID()] = process;

        process = new CSSessionProcess(id,p);
        pm[process->uniqueID()] = process;

        process = new CSVideoProcess(id,p);
        pm[process->uniqueID()] = process;

        process = new CSVoiceProcess(id,p);
        pm[process->uniqueID()] = process;

        QObject::connect(tcp,SIGNAL(readyRead()),p,SLOT(tcpRead()));
    }

    bool createTcp()
    {
        if(tcp->state()!=QAbstractSocket::ConnectedState)
        {
            tcp->connectToHost(WM_HOST_FAKE,WM_PORT_FAKE);
            return tcp->waitForConnected();
        }
        return true;
    }

    QString error;

    QTcpSocket *tcp;

    int status;
    quint32 id;
    QByteArray pwd;
    WMEncryptKey key;

    quint32 sequence;
    quint8 protoType;
    char localDevice[24];
    quint8 network;
    char version[6];

    QMap<QString,QVariant> map;

    QMap<quint16,AbstractCSProcess *> pm;
    ClientService *p;
};

ClientService::ClientService(QObject *parent)
    :AbstractService(parent)
    ,p_d(new ClientServicePrivate(this))
{
    p_d->init();
}

ClientService::~ClientService()
{
    delete p_d;
}

void ClientService::flush(QString key)
{
    Q_UNUSED(key)
}

void ClientService::flush(QVariant key)
{
    qDebug() << "key" << key;

    if(!p_d->createTcp())
        emit error(tr("Create TCP Connect failed."));

    QMap<QString,QVariant> map = key.toMap();
    int opt = map["opt"].toInt();
    AbstractCSProcess *process = p_d->pm[opt];
    if(!process)
    {
        emit error(tr("No such process."));
        return ;
    }

    process->syncSend(key);
}

QByteArray ClientService::name()
{
    return "ClientService";
}

QVariant ClientService::getData()
{
    return p_d->map;
}

WMEncryptKey ClientService::encryptKey() const
{
    return p_d->key;
}

bool ClientService::verifyAccount(quint32 id, const QByteArray &pwd) const
{
    if(id==p_d->id && pwd==p_d->pwd)
        return true;

    return false;
}

int ClientService::loginStatus() const
{
    return p_d->status;
}

void ClientService::setLoginStatus(int status)
{
    p_d->status = status;
}

bool ClientService::startLogin(quint32 id, const QByteArray &pwd)
{
    Q_UNUSED(id)
    Q_UNUSED(pwd)

    /* create a connection to wm server. */
    p_d->tcp->connectToHost(WM_HOST_FAKE,WM_PORT_FAKE);
    if(!p_d->tcp->waitForConnected())
    {
        p_d->error = p_d->tcp->errorString();
        return false;
    }
    return true;
}

QString ClientService::error() const
{
    return p_d->error;
}

bool ClientService::sendData(const QByteArray &data)
{
    Q_UNUSED(data)
    return true;
}

bool ClientService::sendData(const char *data, quint32 data_len)
{
    p_d->tcp->write(data,data_len);
    bool ret = p_d->tcp->waitForBytesWritten();

    if(!ret)
        p_d->error = p_d->tcp->errorString();

    return ret;
}

bool ClientService::sendPackage(wm_protocol_t *proto)
{
    WMEncryptKey key = encryptKey();
    protocol_package *package = package_wmp(proto,key.key,key.key_len);

    if(!package)
    {
        p_d->error = tr("WMP error, package failed.");
        return false;
    }
    bool ret = sendData(package->data,package->length);
    if(!ret)
    {
        p_d->error = tr("WMP error, send failed.");
        return false;
    }
    p_d->sequence++;
    return true;
}

quint32 ClientService::userID() const
{
    return p_d->id;
}

void ClientService::setUserID(quint32 id)
{
    p_d->id = id;
}

quint16 ClientService::protoType() const
{
    return p_d->protoType;
}

void ClientService::localDevice(char *device)
{
    memcpy(device,p_d->localDevice,24);
}

quint8 ClientService::network() const
{
    return p_d->network;
}

quint32 ClientService::time() const
{
    return QTime::currentTime().second();
}

void ClientService::protoVersion(char *version)
{
    memcpy(version,p_d->version,12);
}

quint32 ClientService::protoSequence() const
{
    return p_d->sequence;
}

void ClientService::setEncryptKey(const WMEncryptKey &key) const
{
    memcpy(p_d->key.key,key.key,key.key_len);
    p_d->key.key_len = key.key_len;
}

void ClientService::setData(const QString &key, const QVariant &d)
{
    p_d->map[key] = d;
}

void ClientService::resetData()
{
    p_d->map.clear();
    p_d->map["service"] = "ClientService";
}

void ClientService::tcpRead()
{
    static bool left_flag = false;
    static char left_data[1024*16]="";
    static quint32 left_data_size = 0;
    quint32 left_data_offset = 0;

    char dispose_data[1024*256] = "";
    quint32 dispose_data_size = 0;

    QList<protocol_package *> list;

    QByteArray recv_data = p_d->tcp->readAll();

    qDebug() << "length:" << recv_data.length();
    if(recv_data.size()<=0)
        return ;

    if(left_flag)
    {
        memcpy(dispose_data,left_data,left_data_size);
        dispose_data_size+=left_data_size;
    }

    memcpy(dispose_data+dispose_data_size,recv_data.data(),recv_data.size());
    dispose_data_size+=recv_data.size();

    for(quint32 i=0;i<dispose_data_size;)
    {
        if((i+2)>=dispose_data_size)
            break;

        quint32 len = ntohl(*(quint32 *)(dispose_data+i+13));

        if((i+len)>dispose_data_size || len <= 16)
        {
            i++;
            continue;
        }

        if(*(quint8 *)(dispose_data+i)==WMP_HEAD_ID && *(quint8*)(dispose_data+i+len-1)==WMP_TAIL_ID)
        {
            quint32 p_crc_code = *(quint32 *)(dispose_data+i+1);
            quint32 crc_code = crc32_check_char_buffer(dispose_data+i+5,len-6);
//            if(p_crc_code==crc_code)
            {
                protocol_package *package = allocate_package(len);
                memcpy(package->data,dispose_data+i,len);
                list.append(package);
                i+=len;
                left_data_offset = i;
                continue;
            }
        }
        i++;
    }

    if(left_data_offset!=dispose_data_size)
    {
        memcpy(left_data,dispose_data+left_data_offset,dispose_data_size-left_data_offset);
        left_data_size = dispose_data_size-left_data_offset;
        left_flag = true;
    }
    else
    {
        left_data_size = 0;
        left_data_offset = 0;
        left_flag = false;
    }

    foreach(protocol_package *package,list)
    {
        wm_protocol_t *p_wm = parser_wmp(package,p_d->key.key,p_d->key.key_len);
        AbstractCSProcess *process = p_d->pm[p_wm->body.param->main_id];
        if(process)
        {
            process->syncRecv(p_wm->body.param,p_wm->body.param_num);
        }
    }
}
