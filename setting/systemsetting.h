#ifndef SYSTEMSETTING_H
#define SYSTEMSETTING_H

#include <QWidget>

namespace Ui {
class SystemSetting;
}

class SystemSetting : public QWidget
{
    Q_OBJECT

public:
    explicit SystemSetting(QWidget *parent = 0);
    ~SystemSetting();
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private slots:
    void on_primary_clicked();

    void on_security_clicked();

    void on_authority_clicked();

private:
    Ui::SystemSetting *ui;
    class SystemSettingPrivate *p_d;
    friend class SystemSettingPrivate;
};

#endif // SYSTEMSETTING_H
