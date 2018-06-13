#include "verifymessage.h"
#include "ui_verifymessage.h"

VerifyMessage::VerifyMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VerifyMessage)
{
    ui->setupUi(this);
}

VerifyMessage::~VerifyMessage()
{
    delete ui;
}
