#include "wmcore.h"
#include "wmcore_p.h"
#include <abstractservice.h>

#include <QDebug>
#include <clientservice.h>

WMCore *WMCore::instance = 0;

WMCore::WMCore(QObject *parent)
    :QThread(parent)
    ,p_d(0)
{

}

WMCore::~WMCore()
{
}

WMCore *WMCore::globalInstance()
{
    if(!instance)
    {
        instance = new WMCore;
        instance->start();
    }
    return instance;
}

void WMCore::registerService(QObject *obj, const QByteArray &service)
{
    /* push register operation to p_d. */
    emit pushRegister(obj,service);
}

QVariant WMCore::getDate(const QByteArray &service)
{
    if(p_d && p_d->map.contains(service))
    {
        AbstractService *as = p_d->map[service].service;
        if(as)
        return as->getData();
    }
    return QVariant();
}

void WMCore::flush(const QByteArray &service, const QString &key)
{
    qDebug() << "WMCore flush" << thread();
    /* push flush operation to Private. */
    emit pushFlush(service,key);
}

void WMCore::flush(const QByteArray &service, const QVariant &key)
{
    emit pushFlush(service,key);
}

QPixmap WMCore::accountHead() const
{
    return p_d->head;
}

void WMCore::setAccountHead(const QPixmap &head)
{
    p_d->head = head;
}

QPixmap WMCore::indexOfHead(quint32 id)
{
    Q_UNUSED(id)
    return QPixmap();
}


void WMCore::run()
{
    if(!p_d)
    {
        p_d = new WMCorePrivate;
        connect(this,SIGNAL(pushRegister(QObject*,QByteArray)),p_d,SLOT(registerService(QObject*,QByteArray)));
        connect(this,SIGNAL(pushFlush(QByteArray,QString)),p_d,SLOT(flush(QByteArray,QString)));
        connect(this,SIGNAL(pushFlush(QByteArray,QVariant)),p_d,SLOT(flush(QByteArray,QVariant)));
        connect(p_d,SIGNAL(pushUpdate(QObject *,QVariant)),this,SLOT(pullUpdate(QObject *,QVariant)));
    }

    exec();

    disconnect(this,SIGNAL(pushRegister(QObject*,QByteArray)),p_d,SLOT(registerService(QObject*,QByteArray)));
    disconnect(this,SIGNAL(pushFlush(QByteArray,QString)),p_d,SLOT(flush(QByteArray,QString)));
    disconnect(this,SIGNAL(pushFlush(QByteArray,QVariant)),p_d,SLOT(flush(QByteArray,QVariant)));
    disconnect(p_d,SIGNAL(pushUpdate(QObject *,QVariant)),this,SLOT(pullUpdate(QObject *,QVariant)));
    delete p_d;
}

void WMCore::pullUpdate(QObject *obj, QVariant data)
{
    obj->setProperty("serviceData",data);
}

void WMCore::pullError(AbstractService *service, QString error)
{
    if(service && p_d->map.contains(service->name()))
        p_d->map[service->name()].obj->setProperty("error",error);
}

WMCorePrivate::WMCorePrivate(QObject *parent)
    :QObject(parent)
{
    cs = new ClientService(parent);
}

WMCorePrivate::~WMCorePrivate()
{

}

void WMCorePrivate::registerService(QObject *obj, QByteArray name)
{
    AbstractService *service = ServiceFactory::createService(name);
    if(!service)
        return ;

    connect(service,SIGNAL(startUpdate(AbstractService *)),this,SLOT(update(AbstractService *)));
    connect(service,SIGNAL(error(AbstractService *,QString)),this,SIGNAL(error(AbstractService *,QString)));
    ServiceInfo info;
    info.obj = obj;
    info.service = service;
    map[name] = info;
}

void WMCorePrivate::update(AbstractService *service)
{
    ServiceInfo info = map[service->name()];
    emit pushUpdate(info.obj,info.service->getData());
}

void WMCorePrivate::flush(QByteArray name, QString key)
{
    if(map.contains(name))
        map[name].service->flush(key);
}

void WMCorePrivate::flush(QByteArray name, QVariant key)
{
    if(map.contains(name))
        map[name].service->flush(key);
}
