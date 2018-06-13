#include "personalfolderclean.h"
#include "ui_personalfolderclean.h"

PersonalFolderClean::PersonalFolderClean(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonalFolderClean)
{
    ui->setupUi(this);
}

PersonalFolderClean::~PersonalFolderClean()
{
    delete ui;
}
