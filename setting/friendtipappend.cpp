#include "friendtipappend.h"
#include "ui_friendtipappend.h"

FriendTipAppend::FriendTipAppend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendTipAppend)
{
    ui->setupUi(this);
}

FriendTipAppend::~FriendTipAppend()
{
    delete ui;
}
