#include "skinsetting.h"
#include "ui_skinsetting.h"

#include <QPainter>
#include <QTimer>
#include <qssloader.h>
#include <windowimpl.h>
#include <wmcore/wmcore.h>

class SkinSettingPrivate : public WindowImpl
{
public:
    SkinSettingPrivate(SkinSetting *parent)
        :WindowImpl(parent)
        ,p(parent)
    {}

    void init()
    {
        p->ui->setupUi(p);
        p->setWindowFlags(Qt::Widget|Qt::FramelessWindowHint);
        p->setAttribute(Qt::WA_TranslucentBackground);
        p->ui->transparent->installEventFilter(p);

        slider = new QSlider(Qt::Vertical);
        slider->setWindowFlags(Qt::Widget|Qt::FramelessWindowHint);
        slider->setVisible(false);
        slider->installEventFilter(p);

        timer.setSingleShot(true);
        timer.setInterval(100);
        QObject::connect(&timer,SIGNAL(timeout()),slider,SLOT(hide()));

        QssLoader::load(slider,"skin-slider");

        itemList.append(p->ui->item1);
        itemList.append(p->ui->item2);
        itemList.append(p->ui->item3);
        itemList.append(p->ui->item4);
        itemList.append(p->ui->item5);
        itemList.append(p->ui->item6);
        itemList.append(p->ui->item7);
        itemList.append(p->ui->item8);
        itemList.append(p->ui->item9);
        itemList.append(p->ui->item10);
        itemList.append(p->ui->item11);
        itemList.append(p->ui->item12);
        itemList.append(p->ui->item13);
        itemList.append(p->ui->item14);
        itemList.append(p->ui->item15);

        WMCore::globalInstance()->registerService(p,"SkinService");
        WMCore::globalInstance()->flush("SkinService");
    }

    void drawBackground(QPainter *painter)
    {
        if(!p)
            return ;

        painter->save();
        painter->fillRect(QRect(borderWidth,borderWidth,w_p->width()-2*borderWidth,w_p->height()-2*borderWidth),bgColor);
        painter->restore();
    }

    void showSlider()
    {
        slider->setVisible(true);
        QPoint point = p->ui->transparent->mapToGlobal(p->ui->transparent->rect().topLeft());
        QPoint pos(point.x(),point.y()-slider->height());
        slider->move(pos);
    }

    SkinSetting *p;

    QSlider *slider;
    QTimer timer;
    QList<QLabel *> itemList;
};

SkinSetting *SkinSetting::singletion = 0;

SkinSetting::SkinSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkinSetting),
    p_d(new SkinSettingPrivate(this))
{
    p_d->init();
}

SkinSetting::~SkinSetting()
{
    delete ui;
    delete p_d;
}

SkinSetting *SkinSetting::instance()
{
    if(!singletion)
        singletion = new SkinSetting;

    return singletion;
}

void SkinSetting::openSettingOption(SettingOption option)
{
    SkinSetting::instance()->setOption(option);

    SkinSetting::instance()->show();
}

void SkinSetting::setError(const QString &error)
{
    Q_UNUSED(error)
}

void SkinSetting::setServiceData(const QVariant &data)
{
    Q_UNUSED(data)
}

void SkinSetting::setOption(SkinSetting::SettingOption option)
{
    switch(option)
    {
    case Skin:
        ui->skin->setChecked(true);
        break;
    case Show:
        ui->show->setChecked(true);
        break;
    case ColoredBubble:
        ui->bubble->setChecked(true);
        break;
    case UIManage:
        ui->uimanage->setChecked(true);
        break;
    }
}

void SkinSetting::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    p_d->drawBackground(&painter);
    p_d->drawWindowEdge(&painter);
    QWidget::paintEvent(event);
}

void SkinSetting::mouseMoveEvent(QMouseEvent *event)
{
    p_d->mouseMoveEvent(event);
    QWidget::mouseMoveEvent(event);
}

void SkinSetting::mousePressEvent(QMouseEvent *event)
{
    p_d->mousePressEvent(event);
    QWidget::mousePressEvent(event);
}

void SkinSetting::mouseReleaseEvent(QMouseEvent *event)
{
    p_d->mouseReleaseEvent(event);
    QWidget::mouseReleaseEvent(event);
}

bool SkinSetting::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==ui->transparent)
    {
        switch(event->type())
        {
        case QEvent::Enter:
            p_d->showSlider();
            break;
        case QEvent::Leave:
            p_d->timer.start();
            break;
        default:
            break;
        }
    }
    if(watched==p_d->slider)
    {
        switch(event->type())
        {
        case QEvent::Enter:
            p_d->timer.stop();
            break;
        case QEvent::Leave:
            p_d->timer.start();
            break;
        default:
            break;
        }
    }
    return QWidget::eventFilter(watched,event);
}

void SkinSetting::on_close_clicked()
{
    hide();
}

void SkinSetting::on_right_clicked(const QModelIndex &index)
{
    if(index.isValid())
    {
        if(!index.row())
            ui->up->setEnabled(false);
        else if(index.row()==(ui->right->count()-1))
            ui->down->setEnabled(false);
        else
        {
            ui->up->setEnabled(true);
            ui->down->setEnabled(true);
        }
    }
}

void SkinSetting::on_up_clicked()
{
    QModelIndex index = ui->right->currentIndex();
    QListWidgetItem *item1 = ui->right->currentItem();
    QListWidgetItem *item2;
    int row;
    if(index.isValid())
    {
        row = index.row();
        ui->right->takeItem(row);
        item2 = ui->right->takeItem(row-1);

        ui->right->insertItem(row-1,item1);
        ui->right->insertItem(row,item2);
        ui->right->setCurrentItem(item1);
        updateUpDown();
    }
}

void SkinSetting::on_down_clicked()
{
    QModelIndex index = ui->right->currentIndex();
    QListWidgetItem *item1 = ui->right->currentItem();
    QListWidgetItem *item2;
    int row;
    if(index.isValid())
    {
        row = index.row();
        ui->right->takeItem(row);
        item2 = ui->right->takeItem(row+1);

        ui->right->insertItem(row,item2);
        ui->right->insertItem(row+1,item1);
        ui->right->setCurrentItem(item1);
        updateUpDown();
    }
}

void SkinSetting::updateUpDown()
{
    QModelIndex index = ui->right->currentIndex();
    if(!index.row())
        ui->up->setEnabled(false);
    else if(index.row()==(ui->right->count()-1))
        ui->down->setEnabled(false);
    else
    {
        ui->up->setEnabled(true);
        ui->down->setEnabled(true);
    }
}

void SkinSetting::on_skin_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->skin_page);
}

void SkinSetting::on_show_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->show_page);
}

void SkinSetting::on_bubble_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->bubble_page);
}

void SkinSetting::on_uimanage_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->ui_page);
}
