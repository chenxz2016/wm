#include "skinservice.h"


#define SKIN_ADDRESS "192.168.0.2/skin/rank_%1.skin"

class SkinServicePrivate
{
public:
    SkinServicePrivate(SkinService *parent)
        :p(parent)
        ,nam(new QNetworkAccessManager(parent))
    {
        QObject::connect(nam, SIGNAL(finished(QNetworkReply*)), p, SLOT(saveSkin(QNetworkReply*)));
        QObject::connect(nam, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
                p, SLOT(readSllError(QNetworkReply*,QList<QSslError>)));
    }

    SkinService *p;

    QNetworkAccessManager *nam;
};

SkinService::SkinService(QObject *parent)
    :AbstractService(parent)
    ,p_d(new SkinServicePrivate(this))
{

}

SkinService::~SkinService()
{
    delete p_d;
}

void SkinService::flush(QString key)
{
    Q_UNUSED(key)
}

void SkinService::flush(QVariant key)
{
    Q_UNUSED(key)
}

QByteArray SkinService::name()
{
    return "SkinService";
}

void SkinService::downloadSkin()
{
    /* download the top 15th skin. */

    for(int i=0;i<15;i++)
        p_d->nam->get(QNetworkRequest(QUrl(QString(SKIN_ADDRESS).arg(i))));;
}

void SkinService::readSllError(QNetworkReply *reply, QList<QSslError> list)
{
    Q_UNUSED(reply)
    Q_UNUSED(list)
}

void SkinService::saveSkin(QNetworkReply *reply)
{
    if(reply)
        reply->deleteLater();
}
