#include "creategroup.h"
#include "ui_creategroup.h"

CreateGroup::CreateGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateGroup)
{
    ui->setupUi(this);
}

CreateGroup::~CreateGroup()
{
    delete ui;
}
