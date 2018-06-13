#ifndef SKINSERVICE_H
#define SKINSERVICE_H

#include "abstractservice.h"
#include "wmglobal.h"
#include <QNetworkReply>
#include <QSslError>

class WM_EXPORT SkinService : public AbstractService
{
    Q_OBJECT
public:
    SkinService(QObject *parent = 0);
    ~SkinService();

    void flush(QString key);
    void flush(QVariant key);
    QByteArray name();
protected:
    void downloadSkin();
    void downloadBubble();
private slots:
    void readSllError(QNetworkReply *reply,QList<QSslError> list);
    void saveSkin(QNetworkReply *reply);
private:
    class SkinServicePrivate *p_d;
    friend class SkinServicePrivate;
};

#endif // SKINSERVICE_H
