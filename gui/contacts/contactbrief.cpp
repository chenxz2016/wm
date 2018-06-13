#include "contactbrief.h"
#include "ui_contactbrief.h"

ContactBrief::ContactBrief(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactBrief)
{
    ui->setupUi(this);
}

ContactBrief::~ContactBrief()
{
    delete ui;
}
