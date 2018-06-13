#ifndef WEATHERVIEW_P_H
#define WEATHERVIEW_P_H

#include <QListWidget>


class WeatherSearchView : public QListWidget
{
    Q_OBJECT
public:
    WeatherSearchView(QWidget *parent = 0);
    ~WeatherSearchView();

protected:
    void keyPressEvent(QKeyEvent *event);
    void focusOutEvent(QFocusEvent *event);
private:
    QWidget *p;
};

#endif // WEATHERVIEW_P_H
