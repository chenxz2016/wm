#include "contactsshieldsetting.h"
#include "ui_contactsshieldsetting.h"

ContactsShieldSetting::ContactsShieldSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactsShieldSetting)
{
    ui->setupUi(this);
}

ContactsShieldSetting::~ContactsShieldSetting()
{
    delete ui;
}
