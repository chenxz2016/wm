#ifndef AUTHORITYSETTING_H
#define AUTHORITYSETTING_H

#include <QWidget>

namespace Ui {
class AuthoritySetting;
}

class AuthoritySetting : public QWidget
{
    Q_OBJECT

public:
    explicit AuthoritySetting(QWidget *parent = 0);
    ~AuthoritySetting();

private:
    Ui::AuthoritySetting *ui;
};

#endif // AUTHORITYSETTING_H
