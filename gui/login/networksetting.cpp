#include "networksetting.h"
#include "ui_networksetting.h"

#include <QPainter>

class NetworkSettingPrivate
{
public:
    NetworkSettingPrivate(NetworkSetting *p)
        :parent(p)
    {}


    NetworkSetting *parent;
};

NetworkSetting::NetworkSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkSetting)
    ,p_d(new NetworkSettingPrivate(this))
{
    ui->setupUi(this);
    connect(ui->ok,SIGNAL(clicked()),this,SIGNAL(save()));
    connect(ui->cancel,SIGNAL(clicked()),this,SIGNAL(cancel()));
}

NetworkSetting::~NetworkSetting()
{
    delete ui;
}

QMap<QString, QVariant> NetworkSetting::networkInfo()
{
    QMap<QString, QVariant> map;


    return map;
}

void NetworkSetting::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QLinearGradient gradient;
    gradient.setStart(rect().left(), 0);
    gradient.setFinalStop(rect().left(), rect().height());
    gradient.setColorAt(0, QColor(0,0,0,0));
    gradient.setColorAt(0.1, QColor(0,0,0,0));
    gradient.setColorAt(0.15, QColor(255,255,255,255));
    gradient.setColorAt(1.0, QColor(255,255,255,255));

    painter.fillRect(rect(),QBrush(gradient));
    QWidget::paintEvent(event);
}

void NetworkSetting::on_ns_type_clicked()
{

}

void NetworkSetting::on_ls_type_clicked()
{

}

void NetworkSetting::on_test_clicked()
{

}
