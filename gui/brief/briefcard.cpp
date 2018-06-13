#include "briefcard.h"
#include "detailscard.h"
#include "ui_briefcard.h"
#include <QPainter>
#include <windowimpl.h>


class BriefCardPrivate : public WindowImpl
{
public:
    BriefCardPrivate(BriefCard *parent)
        :WindowImpl(parent)
        ,p(parent)
        ,details(new DetailsCard)
    {}

    ~BriefCardPrivate(){}

    void init()
    {
        p->ui->setupUi(p);
        p->setWindowFlags(Qt::FramelessWindowHint);
        p->setAttribute(Qt::WA_TranslucentBackground);
    }

    void hideStatus()
    {
        p->ui->device_icon->setVisible(false);
        p->ui->device_text->setVisible(false);
        p->ui->device_network->setVisible(false);
    }

    void showStatus()
    {
        p->ui->device_icon->setVisible(true);
        p->ui->device_text->setVisible(true);
        p->ui->device_network->setVisible(true);
    }

    void setDeviceIcon(int icon)
    {
        switch(icon)
        {
        case 1:
            break;
        }
    }

    void setLevel(int level)
    {
        Q_UNUSED(level)
    }

    void setLightAcition(const QMap<QString,QVariant> &map)
    {
        Q_UNUSED(map)
    }

    void setPhotosWall(const QList<QVariant> &list)
    {
        Q_UNUSED(list)
    }

    BriefCard *p;

    DetailsCard *details;
};

BriefCard::BriefCard(QWidget *parent)
    : QWidget(parent)
    ,ui(new Ui::BriefCard)
    ,p_d(new BriefCardPrivate(this))
{
    p_d->init();
}

BriefCard::~BriefCard()
{
    delete p_d;
}

void BriefCard::setBriefData(const QVariant &data)
{
    if(data.isNull())
        return ;

    QMap<QString,QVariant> map = data.toMap();

    /* set name. */
    ui->name->setText(map["name"].toString());

    /* set sign. */
    QString sign = map["sign"].toString();
    if(sign.isEmpty())
        ui->sign->setVisible(false);
    else
        ui->sign->setText(sign);

    /* set online status. */
    int online = map["online"].toInt();
    switch(online)
    {
    case 0:
        p_d->hideStatus();
        break;
    case 1:
        p_d->showStatus();
        p_d->setDeviceIcon(map["online_icon"].toInt());
        ui->device_text->setText(map["online_text"].toString());
        ui->device_network->setText(map["online_network"].toString());
        break;
    }

    /* set level. */
    int level = map["level"].toInt();
    p_d->setLevel(level);

    /* set light actions. */
    QMap<QString,QVariant> m = map["actions"].toMap();
    p_d->setLightAcition(m);

    /* set photo wall. */
    QList<QVariant> photos = map["photos"].toList();
    p_d->setPhotosWall(photos);

    /* set last chatter. */

}

void BriefCard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    p_d->drawWindowEdge(&painter);
    QWidget::paintEvent(event);
}

void BriefCard::on_name_clicked()
{
    emit requestHide();
    p_d->details->show();
}
