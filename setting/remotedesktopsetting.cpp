#include "remotedesktopsetting.h"
#include "ui_remotedesktopsetting.h"

RemoteDesktopSetting::RemoteDesktopSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoteDesktopSetting)
{
    ui->setupUi(this);
}

RemoteDesktopSetting::~RemoteDesktopSetting()
{
    delete ui;
}
