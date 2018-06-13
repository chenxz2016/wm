#ifndef WEATHERSERVICE_H
#define WEATHERSERVICE_H

#include "abstractservice.h"
#include "wmglobal.h"
#include <QNetworkReply>
#include <QSslError>


class WM_EXPORT WeatherService : public AbstractService
{
    Q_OBJECT
public:
    explicit WeatherService(QObject *parent = 0);
    ~WeatherService();

    void flush(QString key);
    void flush(QVariant key);
    QByteArray name();
signals:
//    void weatherUpdated();
    void error(QString);
private slots:
    void readIP();
    void readError(QNetworkReply::NetworkError error);
    void readSllError(QList<QSslError> list);
    void downloadPosition();
    void downloadCityWeather();
    void downloadProvince();
private:
    class WeatherServicePrivate *p_d;
    friend class WeatherServicePrivate;
};

#endif // WEATHERSERVICE_H
