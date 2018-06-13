#include "autoreplysetting.h"
#include "ui_autoreplysetting.h"

AutoReplySetting::AutoReplySetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoReplySetting)
{
    ui->setupUi(this);
}

AutoReplySetting::~AutoReplySetting()
{
    delete ui;
}
