#include "camerasetting.h"
#include "ui_camerasetting.h"

CameraSetting::CameraSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraSetting)
{
    ui->setupUi(this);
}

CameraSetting::~CameraSetting()
{
    delete ui;
}
