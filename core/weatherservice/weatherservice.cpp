#include "weatherservice.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QNetworkAccessManager>

#include <QXmlStreamReader>


#define IP_GET "http://www.3322.org/dyndns/getip"
#define WEATHER_IP "http://flash.weather.com.cn/wmaps/xml/china.xml"
#define CITY_WEATHER "http://flash.weather.com.cn/wmaps/xml/%1.xml"
#define FIND_CITY "http://ip.taobao.com/service/getIpInfo.php?ip=%1"

class WeatherServicePrivate
{
public:
    WeatherServicePrivate(WeatherService *parent)
        :p(parent)
        ,nam(0)
        ,city_id(-1)
    {}

    void checkUpdate()
    {
        if(replyList.isEmpty() && city_id != -1)
            emit p->startUpdate(p);
    }
    WeatherService *p;

    QNetworkAccessManager *nam;

    QList<QNetworkReply *> replyList;
    QList<QNetworkReply *> removeList;
    QString localHost;
    int city_id;
};

WeatherService::WeatherService(QObject *parent)
    :AbstractService(parent)
    ,p_d(new WeatherServicePrivate(this))
{
    p_d->nam = new QNetworkAccessManager(this);
}

WeatherService::~WeatherService()
{
    delete p_d;
}

void WeatherService::flush(QString key)
{
    Q_UNUSED(key)
    qDebug() << "flush" << thread();
    foreach(QNetworkReply *reply,p_d->removeList)
        delete reply;
    p_d->removeList.clear();

    QNetworkReply *reply;
    reply = p_d->nam->get(QNetworkRequest(QUrl(IP_GET)));
    connect(reply, SIGNAL(readyRead()), this, SLOT(readIP()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(readError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(readSllError(QList<QSslError>)));
    p_d->replyList.append(reply);

    reply = p_d->nam->get(QNetworkRequest(QUrl(WEATHER_IP)));
    connect(reply, SIGNAL(readyRead()), this, SLOT(downloadProvince()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(readError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(readSllError(QList<QSslError>)));
    p_d->replyList.append(reply);
}

void WeatherService::flush(QVariant key)
{
    Q_UNUSED(key)
}

QByteArray WeatherService::name()
{
    return "WeatherService";
}

void WeatherService::downloadCityWeather()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply *>(sender());
    if(!reply)
        return ;

    p_d->replyList.removeAll(reply);
    p_d->removeList.append(reply);

    QXmlStreamReader reader(reply);

    QMap<QString,QVariant> m = d.toMap();
    QString name;
    while(!reader.atEnd())
    {
        QXmlStreamReader::TokenType token = reader.readNext();
        if(token == QXmlStreamReader::StartDocument)
            continue;

        if(token == QXmlStreamReader::StartElement)
        {
            if(m.contains(reader.name().toString()))
            {
                name = reader.name().toString();
                continue;
            }

            /* City Weather Data. */
            if(m.contains(name))
            {
                QXmlStreamAttributes attr = reader.attributes();
                QString pyName = attr.value("pyName").toString();
                if(!pyName.isEmpty())
                {
                    QMap<QString,QVariant> mm = m[name].toMap();
                    QMap<QString,QVariant> _map = mm["cities"].toMap();
                    QMap<QString,QVariant> map;
                    map["pyName"] = pyName;
                    map["windState"] = attr.value("windState").toString();
                    map["temp1"] = attr.value("temp1").toString();
                    map["temp2"] = attr.value("temp2").toString();
                    map["details"] = attr.value("stateDetailed").toString();
                    map["state1"] = attr.value("state1").toString();
                    map["state2"] = attr.value("state2").toString();
                    map["cityname"] = mm["quName"].toString() + "-" + attr.value("cityname").toString();
                    map["quName"] = mm["quName"].toString() + "-" +attr.value("quName").toString();
                    map["centername"] = mm["quName"].toString() + "-" + attr.value("centername").toString();
                    map["temNow"] = attr.value("temNow").toString();
                    map["windDir"] = attr.value("windDir").toString();
                    map["windPower"] = attr.value("windPower").toString();
                    map["humidity"] = attr.value("humidity").toString();
                    map["time"] = attr.value("time").toString();
                    map["url"] = attr.value("url").toString();
                    _map[pyName] = map;
                    mm["cities"] = _map;
                    m[name] = mm;
                }
            }
        }
    }
    d = m;

    p_d->checkUpdate();
}

void WeatherService::downloadProvince()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply *>(sender());
    if(!reply)
        return ;

    p_d->replyList.removeAll(reply);
    p_d->removeList.append(reply);

    QXmlStreamReader reader(reply);

    QMap<QString,QVariant> m = d.toMap();
    while(!reader.atEnd())
    {
        QXmlStreamReader::TokenType token = reader.readNext();
        if(token == QXmlStreamReader::StartDocument)
            continue;

        if(token == QXmlStreamReader::StartElement)
        {
            if(reader.name() == "china")
                continue;

            /* City Weather Data. */
            if(reader.name() == "city")
            {
                QXmlStreamAttributes attr = reader.attributes();
                QString pyName = attr.value("pyName").toString();
                if(!pyName.isEmpty())
                {
                    QMap<QString,QVariant> map = m[pyName].toMap();
                    map["pyName"] = pyName;
                    map["windState"] = attr.value("windState").toString();
                    map["temp1"] = attr.value("temp1").toString();
                    map["temp2"] = attr.value("temp2").toString();
                    map["details"] = attr.value("stateDetailed").toString();
                    map["state1"] = attr.value("state1").toString();
                    map["state2"] = attr.value("state2").toString();
                    map["cityname"] = attr.value("cityname").toString();
                    map["quName"] = attr.value("quName").toString();
                    m[pyName] = map;
                }
            }
        }
    }
    d = m;

    QStringList l = m.keys();
    foreach(QString city,l)
    {
        reply = p_d->nam->get(QNetworkRequest(QUrl(QString(CITY_WEATHER).arg(city))));
        connect(reply, SIGNAL(readyRead()), this, SLOT(downloadCityWeather()));
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
                this, SLOT(readError(QNetworkReply::NetworkError)));
        connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
                this, SLOT(readSllError(QList<QSslError>)));
        p_d->replyList.append(reply);
    }
}

void WeatherService::readIP()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
    if(reply)
    {
        p_d->localHost= reply->readAll();
        qDebug() << "WeatherService[IP]:" << p_d->localHost;

        p_d->replyList.removeAll(reply);
        p_d->removeList.append(reply);

        reply = p_d->nam->get(QNetworkRequest(QUrl(QString(FIND_CITY).arg(p_d->localHost))));
        connect(reply, SIGNAL(readyRead()), this, SLOT(downloadPosition()));
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
                this, SLOT(readError(QNetworkReply::NetworkError)));
        connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
                this, SLOT(readSllError(QList<QSslError>)));
        p_d->replyList.append(reply);
    }
}

void WeatherService::readError(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error)
}

void WeatherService::readSllError(QList<QSslError> list)
{
    Q_UNUSED(list)
}

void WeatherService::downloadPosition()
{
    QNetworkReply *reply = dynamic_cast<QNetworkReply *>(sender());
    if(!reply)
        return ;

    p_d->replyList.removeAll(reply);
    p_d->removeList.append(reply);
    qDebug() << "read json";
    QString content = reply->readAll();
    if(content.isEmpty())
        return ;

    QJsonDocument  json = QJsonDocument::fromJson(content.toUtf8());
    QJsonObject  sett2 = json.object();
    QJsonValue value = sett2.value("data");
    QJsonObject i = value.toObject();
    p_d->city_id = i["city_id"].toString().toInt();

    QMap<QString,QVariant> m = d.toMap();
    m["city_id"] = p_d->city_id;
    d = m;

    p_d->checkUpdate();
}
