#include "talkwarntip.h"

#include "ui_talkwarntip.h"

#include <QPainter>
#include <QTimer>

TalkWarnTip::TalkWarnTip(QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::TalkWarnTip)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->setInterval(1000*5);
    timer->setSingleShot(true);
    connect(timer,SIGNAL(timeout()),this,SLOT(hide()));
    connect(ui->close,SIGNAL(clicked(bool)),this,SLOT(hide()));
}

TalkWarnTip::~TalkWarnTip()
{
    delete ui;
}

void TalkWarnTip::setWarnText(const QString &text)
{
    ui->warn->setText(text);
}

QString TalkWarnTip::warnText() const
{
    return ui->warn->text();
}

void TalkWarnTip::pop(const QSize &size,const QString &warning)
{
    if(!isVisible())
    {
        setWarnText(warning);
        setVisible(true);
    }
    resize(size);
    timer->start();
}

void TalkWarnTip::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(),QColor(129, 194, 255));
    QWidget::paintEvent(event);
}
