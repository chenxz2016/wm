#ifndef CONTACTSSHIELDSETTING_H
#define CONTACTSSHIELDSETTING_H

#include <QWidget>

namespace Ui {
class ContactsShieldSetting;
}

class ContactsShieldSetting : public QWidget
{
    Q_OBJECT

public:
    explicit ContactsShieldSetting(QWidget *parent = 0);
    ~ContactsShieldSetting();

private:
    Ui::ContactsShieldSetting *ui;
};

#endif // CONTACTSSHIELDSETTING_H
