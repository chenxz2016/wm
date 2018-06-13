#include "weathersetting.h"
#include "ui_weathersetting.h"

WeatherSetting::WeatherSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeatherSetting)
{
    ui->setupUi(this);
}

WeatherSetting::~WeatherSetting()
{
    delete ui;
}
