#include "systemsetting.h"
#include "ui_systemsetting.h"

#include <QPainter>
#include <windowimpl.h>

class SystemSettingPrivate : public WindowImpl
{
public:
    SystemSettingPrivate(SystemSetting *parent)
        :WindowImpl(parent)
        ,p(parent)
    {}

    void init()
    {
        p->ui->setupUi(p);
        p->setWindowFlags(Qt::Widget|Qt::FramelessWindowHint);
        p->setAttribute(Qt::WA_TranslucentBackground);
        p->setAutoFillBackground(false);
    }

    SystemSetting *p;
};

SystemSetting::SystemSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemSetting),
    p_d(new SystemSettingPrivate(this))
{
    p_d->init();
}

SystemSetting::~SystemSetting()
{
    delete ui;
}

void SystemSetting::mouseMoveEvent(QMouseEvent *event)
{
    p_d->mouseMoveEvent(event);
    QWidget::mouseMoveEvent(event);
}

void SystemSetting::mousePressEvent(QMouseEvent *event)
{
    p_d->mousePressEvent(event);
    QWidget::mousePressEvent(event);
}

void SystemSetting::mouseReleaseEvent(QMouseEvent *event)
{
    p_d->mouseReleaseEvent(event);
    QWidget::mouseReleaseEvent(event);
}

void SystemSetting::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    p_d->drawBackground(&painter);
    p_d->drawWindowEdge(&painter);
    QWidget::paintEvent(event);
}

void SystemSetting::on_primary_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->primary_page);
}

void SystemSetting::on_security_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->security_page);
}

void SystemSetting::on_authority_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->authority_page);
}
