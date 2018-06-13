#include "warningtonesetting.h"
#include "ui_warningtonesetting.h"

WarningToneSetting::WarningToneSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WarningToneSetting)
{
    ui->setupUi(this);
}

WarningToneSetting::~WarningToneSetting()
{
    delete ui;
}
