#include "hotkeysetting.h"
#include "ui_hotkeysetting.h"

HotkeySetting::HotkeySetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotkeySetting)
{
    ui->setupUi(this);
}

HotkeySetting::~HotkeySetting()
{
    delete ui;
}
