#include "repost.h"
#include "ui_repost.h"

Repost::Repost(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Repost)
{
    ui->setupUi(this);
}

Repost::~Repost()
{
    delete ui;
}
