#include "warning.h"
#include "ui_warning.h"

Warning::Warning(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Warning)
{
    ui->setupUi(this);
}

Warning::~Warning()
{
    delete ui;
}
