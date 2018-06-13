#ifndef ABSTRACTSERVICE_H
#define ABSTRACTSERVICE_H

#include <QObject>
#include <QVariant>
#include "wmglobal.h"

class WM_EXPORT AbstractService : public QObject
{
    Q_OBJECT
public:
    AbstractService(QObject *parent = 0);
    virtual ~AbstractService();

    virtual void flush(QString) = 0;
    virtual void flush(QVariant) = 0;
    virtual QByteArray name() = 0;
    virtual QVariant getData();
signals:
    void startUpdate(AbstractService *service);
    void error(AbstractService *,QString);
protected:
    QVariant d;
};

class ServiceFactory
{
public:
    static AbstractService *createService(const QByteArray &service);
};

#endif // ABSTRACTSERVICE_H
