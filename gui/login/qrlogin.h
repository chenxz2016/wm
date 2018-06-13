#ifndef QRLOGIN_H
#define QRLOGIN_H

#include <QWidget>

namespace Ui {
class QRLogin;
}

class QRLogin : public QWidget
{
    Q_OBJECT

public:
    explicit QRLogin(QWidget *parent = 0);
    ~QRLogin();
signals:
    void goBack();
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::QRLogin *ui;
};

#endif // QRLOGIN_H
