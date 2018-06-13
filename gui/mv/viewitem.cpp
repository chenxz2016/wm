#include "viewitem.h"
#include "ui_viewitem.h"

ViewItem::ViewItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewItem)
{
    ui->setupUi(this);
}

ViewItem::~ViewItem()
{
    delete ui;
}
