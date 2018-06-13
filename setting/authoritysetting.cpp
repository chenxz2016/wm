#include "authoritysetting.h"
#include "ui_authoritysetting.h"

AuthoritySetting::AuthoritySetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthoritySetting)
{
    ui->setupUi(this);
}

AuthoritySetting::~AuthoritySetting()
{
    delete ui;
}
