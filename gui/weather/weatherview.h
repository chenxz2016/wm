#ifndef WEATHERVIEW_H
#define WEATHERVIEW_H

#include <QStackedWidget>

namespace Ui {
class WeatherView;
}

class QListWidgetItem;

class WeatherView : public QStackedWidget
{
    Q_OBJECT
    Q_PROPERTY(QString error WRITE setError)
    Q_PROPERTY(QVariant serviceData WRITE setServiceData)
public:
    explicit WeatherView(QWidget *parent = 0);
    ~WeatherView();

    bool animationEnable()const;
    void setAnimationEnable(bool enable);

    void setError(const QString &error);
    void setServiceData(const QVariant &data);
public slots:
    void citySelected(QListWidgetItem *item);
protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void moveEvent(QMoveEvent *event);
private slots:

    void on_setting_clicked();

    void on_finish_clicked();

    void on_input_textChanged(const QString &arg1);

    void on_first_textChanged(const QString &arg1);

    void on_second_textChanged(const QString &arg1);

    void on_third_textChanged(const QString &arg1);

private:
    Ui::WeatherView *ui;
    class WeatherViewPrivate *p_d;
    friend class WeatherViewPrivate;
};

#endif // WEATHERVIEW_H
