#ifndef NETWORKSETTING_H
#define NETWORKSETTING_H

#include <QWidget>

namespace Ui {
class NetworkSetting;
}

class NetworkSetting : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkSetting(QWidget *parent = 0);
    ~NetworkSetting();

    QMap<QString,QVariant> networkInfo();
signals:
    void cancel();
    void save();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_ns_type_clicked();

    void on_ls_type_clicked();

    void on_test_clicked();

private:
    Ui::NetworkSetting *ui;
    class NetworkSettingPrivate *p_d;
    friend class NetworkSettingPrivate;
};

#endif // NETWORKSETTING_H
