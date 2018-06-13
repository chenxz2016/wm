#include "application.h"

#include <QFile>
#include <QMap>
#include <QDebug>

extern QMap<int,int> city_id_url;

WMApplication::WMApplication()
{

}

static void init_weather_lookinto_map()
{
    QFile file(":/res/weather/cities.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << file.errorString();
        return ;
    }

    while(!file.atEnd())
    {
        QString line = file.readLine();
        if(line.isEmpty() || line.startsWith("#") || line.startsWith("//"))
            continue;

        QStringList l = line.split(" ");
        if(l.count()>=2)
            city_id_url[l.at(0).toInt()] = l.at(1).toInt();
    }
}

void WMApplication::init()
{
    /* init weather lookinto map. */
    init_weather_lookinto_map();
}
