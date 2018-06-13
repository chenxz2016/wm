#include "personcard.h"
#include "ui_personcard.h"
#include "ui_shortintroduction.h"
#include "windowimpl.h"

#include <QTimer>
#include <QDebug>
#include <QPainter>

class PersonCardPrivate
{
public:
    PersonCardPrivate(PersonCard *parent)
        :p(parent)
    {}

    PersonCard *p;
};

PersonCard::PersonCard(QWidget *parent) :
    QWidget(0),
    ui(new Ui::PersonCard),
    p_d(new PersonCardPrivate(this))
{
    Q_UNUSED(parent)
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

PersonCard::~PersonCard()
{
    delete ui;
}

void PersonCard::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}


class ShortIntroductionPrivate : public WindowImpl
{
public:
    ShortIntroductionPrivate(ShortIntroduction *parent)
        :WindowImpl(parent)
        ,p(parent)
    {}
    ~ShortIntroductionPrivate(){}

    ShortIntroduction *p;
};

ShortIntroduction::ShortIntroduction(QWidget *parent)
    :QWidget(0)
    ,ui(new Ui::ShortIntroduction)
{
    Q_UNUSED(parent)
    setObjectName("shortindtroduction");

    ui->setupUi(this);

    p_d = new ShortIntroductionPrivate(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

ShortIntroduction::~ShortIntroduction()
{

}


void ShortIntroduction::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    p_d->drawWindowEdge(&painter);
    QWidget::paintEvent(event);
}
