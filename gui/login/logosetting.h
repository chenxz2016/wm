#ifndef LOGOSETTING_H
#define LOGOSETTING_H

#include <QWidget>

namespace Ui {
class LogoSetting;
}

class LogoSetting : public QWidget
{
    Q_OBJECT

public:
    explicit LogoSetting(QWidget *parent = 0);
    ~LogoSetting();

signals:
    void cancel();
    void save();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_flush_clicked();

private:
    Ui::LogoSetting *ui;
};

#endif // LOGOSETTING_H
