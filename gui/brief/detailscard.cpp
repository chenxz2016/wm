#include "detailscard.h"
#include "ui_detailscard.h"
#include "windowimpl.h"

#include <QTimer>
#include <QDebug>
#include <QPainter>

class DetailsCardPrivate : public WindowImpl
{
public:
    DetailsCardPrivate(DetailsCard *parent)
        :WindowImpl(parent)
        ,p(parent)
    {}

    void init()
    {
        p->ui->setupUi(p);

        p->setWindowFlags(Qt::FramelessWindowHint);
        p->setAttribute(Qt::WA_TranslucentBackground);
    }

    DetailsCard *p;
};

DetailsCard::DetailsCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailsCard),
    p_d(new DetailsCardPrivate(this))
{
    p_d->init();
}

DetailsCard::~DetailsCard()
{
    delete ui;
    delete p_d;
}

void DetailsCard::mouseMoveEvent(QMouseEvent *event)
{
    p_d->mouseMoveEvent(event);
    QWidget::mouseMoveEvent(event);
}

void DetailsCard::mousePressEvent(QMouseEvent *event)
{
    p_d->mousePressEvent(event);
    QWidget::mousePressEvent(event);
}

void DetailsCard::mouseReleaseEvent(QMouseEvent *event)
{
    p_d->mouseReleaseEvent(event);
    QWidget::mousePressEvent(event);
}

void DetailsCard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    p_d->drawWindowEdge(&painter);
    QWidget::paintEvent(event);
}


