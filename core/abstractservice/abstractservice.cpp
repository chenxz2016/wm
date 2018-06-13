#include "abstractservice.h"

#include <clientservice.h>
#include <weatherservice.h>

AbstractService::AbstractService(QObject *parent)
    :QObject(parent)
{
}

AbstractService::~AbstractService()
{

}

QVariant AbstractService::getData()
{
    return d;
}

AbstractService *ServiceFactory::createService(const QByteArray &service)
{
    AbstractService *as = 0;
    if(service=="WeatherService")
        as = new WeatherService;
    else if(service=="ClientService")
        as = new ClientService;

    return as;
}
