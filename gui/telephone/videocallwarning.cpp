#include "videocallwarning.h"
#include "ui_videocallwarning.h"

VideoCallWarning::VideoCallWarning(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoCallWarning)
{
    ui->setupUi(this);
}

VideoCallWarning::~VideoCallWarning()
{
    delete ui;
}

QString VideoCallWarning::warning() const
{
    return ui->text->text();
}

void VideoCallWarning::setWarning(const QString &warning)
{
    ui->text->setText(warning);
}
