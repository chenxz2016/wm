#include "qrlogin.h"
#include "ui_qrlogin.h"

#include <QPainter>

QRLogin::QRLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QRLogin)
{
    ui->setupUi(this);
    ui->tip->hide();
    connect(ui->back,SIGNAL(clicked()),this,SIGNAL(goBack()));
}

QRLogin::~QRLogin()
{
    delete ui;
}

void QRLogin::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QLinearGradient gradient;
    gradient.setStart(rect().left(), 0);
    gradient.setFinalStop(rect().left(), rect().height());
    gradient.setColorAt(0, QColor(0,0,0,0));
    gradient.setColorAt(0.15, QColor(0,0,0,0));
    gradient.setColorAt(0.2, QColor(255,255,255,255));
    gradient.setColorAt(1.0, QColor(255,255,255,255));

    painter.fillRect(rect(),QBrush(gradient));
    QWidget::paintEvent(event);
}
