#include "enshrien.h"
#include "ui_enshrien.h"

Enshrien::Enshrien(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Enshrien)
{
    ui->setupUi(this);
}

Enshrien::~Enshrien()
{
    delete ui;
}
