#include "fileassistance.h"
#include "ui_fileassistance.h"

FileAssistance::FileAssistance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileAssistance)
{
    ui->setupUi(this);
}

FileAssistance::~FileAssistance()
{
    delete ui;
}
