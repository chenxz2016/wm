#include "logosetting.h"
#include "ui_logosetting.h"

#include <QPainter>

LogoSetting::LogoSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogoSetting)
{
    ui->setupUi(this);

    connect(ui->ok,SIGNAL(clicked()),this,SIGNAL(save()));
    connect(ui->cancel,SIGNAL(clicked()),this,SIGNAL(cancel()));
}

LogoSetting::~LogoSetting()
{
    delete ui;
}

void LogoSetting::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(),QBrush(Qt::white));
    QWidget::paintEvent(event);
}

void LogoSetting::on_flush_clicked()
{

}
