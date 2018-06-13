#include "connectiontip.h"
#include "ui_connectiontip.h"

ConnectionTip::ConnectionTip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionTip)
{
    ui->setupUi(this);
}

ConnectionTip::~ConnectionTip()
{
    delete ui;
}

void ConnectionTip::show()
{
    setFocus();
    QWidget::show();
}

void ConnectionTip::setSpeakerState(ConnectionTip::State state, const QString &desc)
{
    if(state==Normal)
    {
        ui->ms_status->setPixmap(QPixmap(":/res/telephone/mus.png"));
        if(!desc.isEmpty())
            ui->ms_desc->setText(desc);
    }
    else if(state==Unormal)
    {
        ui->ms_status->setPixmap(QPixmap(":/res/telephone/gbe.png"));
        if(!desc.isEmpty())
            ui->ms_desc->setText(desc);
    }
}

void ConnectionTip::setMicrophoneState(ConnectionTip::State state, const QString &desc)
{
    if(state==Normal)
    {
        ui->ms_status->setPixmap(QPixmap(":/res/telephone/mus.png"));
        if(!desc.isEmpty())
            ui->ms_desc->setText(desc);
    }
    else if(state==Unormal)
    {
        ui->ms_status->setPixmap(QPixmap(":/res/telephone/gbe.png"));
        if(!desc.isEmpty())
            ui->ms_desc->setText(desc);
    }
}

void ConnectionTip::setCameraState(ConnectionTip::State state, const QString &desc)
{
    if(state==Normal)
    {
        ui->camera_status->setPixmap(QPixmap(":/res/telephone/mus.png"));
        if(!desc.isEmpty())
            ui->camera_desc->setText(desc);
    }
    else if(state==Unormal)
    {
        ui->camera_status->setPixmap(QPixmap(":/res/telephone/gbe.png"));
        if(!desc.isEmpty())
            ui->camera_desc->setText(desc);
    }
}

void ConnectionTip::setNetworkState(ConnectionTip::State state, const QString &desc)
{
    if(state==Normal)
    {
        ui->ns_status->setPixmap(QPixmap(":/res/telephone/mus.png"));
        if(!desc.isEmpty())
            ui->ns_desc->setText(desc);
    }
    else if(state==Unormal)
    {
        ui->ns_status->setPixmap(QPixmap(":/res/telephone/gbe.png"));
        if(!desc.isEmpty())
            ui->ns_desc->setText(desc);
    }
}

void ConnectionTip::setSystemState(ConnectionTip::State state, const QString &desc)
{
    if(state==Normal)
    {
        ui->ns_status->setPixmap(QPixmap(":/res/telephone/mus.png"));
        if(!desc.isEmpty())
            ui->ns_desc->setText(desc);
    }
    else if(state==Unormal)
    {
        ui->ns_status->setPixmap(QPixmap(":/res/telephone/gbe.png"));
        if(!desc.isEmpty())
            ui->ns_desc->setText(desc);
    }
}

void ConnectionTip::focusOutEvent(QFocusEvent *event)
{
    hide();
    QWidget::focusOutEvent(event);
}
