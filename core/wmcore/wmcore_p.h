#ifndef WMCORE_P_H
#define WMCORE_P_H

#include <QMap>
#include <QObject>
#include <QPixmap>
#include <QVariant>

class AbstractService;
class ClientService;

struct ServiceInfo
{
    QObject *obj;
    AbstractService *service;
};

class WMCorePrivate : public QObject
{
    Q_OBJECT
public:
    WMCorePrivate(QObject *parent = 0);
    ~WMCorePrivate();

    QMap<QByteArray,ServiceInfo> map;
    QPixmap head;
    ClientService *cs;
signals:
    void pushUpdate(QObject *,QVariant);
    void error(AbstractService *,QString);
private slots:
    void registerService(QObject *obj,QByteArray service);
    void update(AbstractService *service);
    void flush(QByteArray name,QString key);
    void flush(QByteArray name,QVariant key);
};

#endif // WMCORE_P_H
