#ifndef WMCORE_H
#define WMCORE_H

#include <QPixmap>
#include <QThread>
#include <QVariant>
#include "wmglobal.h"

class AbstractService;

class WM_EXPORT WMCore : public QThread
{
    Q_OBJECT
    Q_PROPERTY(QPixmap accountHead READ accountHead WRITE setAccountHead)
public:
    WMCore(QObject *parent = 0);
    ~WMCore();

    static WMCore *globalInstance();
    /* register service. */
    void registerService(QObject *obj,const QByteArray &service);

    /* get service data. */
    QVariant getDate(const QByteArray &service);

    /* flush service data. */
    void flush(const QByteArray &service,const QString &key = "");
    void flush(const QByteArray &service,const QVariant &key);

    QPixmap accountHead()const;
    void setAccountHead(const QPixmap &head);

    QPixmap indexOfHead(quint32 id);

signals:
    /* push register operation to Private object. */
    void pushRegister(QObject *obj,QByteArray name);

    /* push update from service to object. */
    void pushUpdate(QString key);

    /* push flush operation to Private. */
    void pushFlush(QByteArray service, QString key);
    void pushFlush(QByteArray service, QVariant key);

    void pushData(QVariant);
protected:
    void run();
private slots:
    /* pull update from Private. */
    void pullUpdate(QObject *,QVariant);

    /* pull error from Private. */
    void pullError(AbstractService *,QString);
private:
    class WMCorePrivate *p_d;
    friend class WMCorePrivate;
    static WMCore *instance;
};

#endif // WMCORE_H
