#include "filerecorditem.h"
#include "ui_filerecorditem.h"

FileRecordItem::FileRecordItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileRecordItem)
{
    ui->setupUi(this);
}

FileRecordItem::~FileRecordItem()
{
    delete ui;
}
