#ifndef WEATHERSETTING_H
#define WEATHERSETTING_H

#include <QWidget>

namespace Ui {
class WeatherSetting;
}

class WeatherSetting : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherSetting(QWidget *parent = 0);
    ~WeatherSetting();

private:
    Ui::WeatherSetting *ui;
};

#endif // WEATHERSETTING_H
