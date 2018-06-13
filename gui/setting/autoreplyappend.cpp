#include "autoreplyappend.h"
#include "ui_autoreplyappend.h"

AutoReplyAppend::AutoReplyAppend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoReplyAppend)
{
    ui->setupUi(this);
}

AutoReplyAppend::~AutoReplyAppend()
{
    delete ui;
}
