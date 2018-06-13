#include "weatherview.h"
#include "weatherview_p.h"
#include "ui_weatherview.h"

#include <QListWidget>
#include <QMouseEvent>
#include <QPainter>
#include <qssloader.h>
#include "windowimpl.h"
#include <wmcore/wmcore.h>
#include <QDebug>
#include "turn/wmturn.h"
#include "turn/wmturn_p.h"

QMap<int,int> city_id_url;

class WeatherData
{
public:
    QString pyName;
    QString quName;
    QString windState;
    qint8 temp1;
    qint8 temp2;
    QString details;
    qint8 state1;
    qint8 state2;
    QString cityName;
    QString centerName;
    qint8 temNow;
    QString windDir;
    QString windPower;
    QString humidity;
    QString time;
    int url;
};


class WeatherViewPrivate : public WindowImpl
{
public:
    WeatherViewPrivate(WeatherView *parent)
        :WindowImpl(parent)
        ,p(parent)
        ,animationEnable(true)
    {
        bgColor = Qt::gray;
    }
    ~WeatherViewPrivate(){}

    void init()
    {
        WMCore::globalInstance();
        p->ui->setupUi(p);
        p->ui->input->installEventFilter(p);

        search = new WeatherSearchView(p->ui->input);
        search->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        search->setVisible(false);
        QObject::connect(search,SIGNAL(itemClicked(QListWidgetItem*)),p,SLOT(citySelected(QListWidgetItem *)));

        QssLoader::load(search,"weather-search-view");

        p->setWindowFlags(Qt::FramelessWindowHint);
        p->setAttribute(Qt::WA_TranslucentBackground);
        p->setGraphicsEffect(new GraphicsTurnEffect);

        WMCore::globalInstance()->registerService(p,"WeatherService");
        WMCore::globalInstance()->flush("WeatherService");
    }

    void drawBackground(QPainter *painter)
    {
        if(!p)
            return ;

        painter->save();
        painter->fillRect(borderWidth,borderWidth,p->width()-2*borderWidth,p->height()-2*borderWidth,bgColor);
        painter->restore();
    }

    void inputChanged(const QString &text)
    {
        if(text.isEmpty())
        {
            search->setVisible(false);
            return ;
        }

        search->clear();
        QStringList list;
        QList<int> l = city_id_map.keys();
        foreach(int key,l)
        {
            if(city_id_map[key]->pyName.startsWith(text))
            {
                list.append(city_id_map[key]->quName);
                if(list.count()>=5)
                    break;
            }
            else if(city_id_map[key]->quName.startsWith(text))
            {
                list.append(city_id_map[key]->quName);
                if(list.count()>=5)
                    break;
            }
        }

        search->addItems(list);

        updatesearch();
        search->setVisible(true);
    }
    void updatesearch()
    {
        search->setFixedWidth(p->ui->input->width());
        QPoint pos = p->ui->input->rect().bottomLeft();
        search->move(p->ui->input->mapToGlobal(pos));
    }

    WeatherView *p;

    QMap<int,WeatherData *> city_id_map;
    QMap<QString,WeatherData *> pyname_map;
    QMap<QString,WeatherData *> quname_map;
    int city_id;
    bool animationEnable;
    QListWidget *search;
};

WeatherView::WeatherView(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::WeatherView),
    p_d(new WeatherViewPrivate(this))
{
    p_d->init();
}

WeatherView::~WeatherView()
{
    delete p_d;
    delete ui;
}

bool WeatherView::animationEnable() const
{
    return p_d->animationEnable;
}

void WeatherView::setAnimationEnable(bool enable)
{
    p_d->animationEnable = enable;
}

void WeatherView::setError(const QString &error)
{
    Q_UNUSED(error)
}

void WeatherView::setServiceData(const QVariant &data)
{
    /* update weather data. */
    qDebug() << "set service data";
    QMap<QString,QVariant> map = data.toMap();
    p_d->city_id = map["city_id"].toInt();

    QStringList keys = map.keys();
    foreach(QString key,keys)
    {
        WeatherData *d;// = new WeatherData;
//        d->pyName = pyName;
//        d->windState = map[key].toMap()["pyName"];
//        d->temp1 = map[key].toMap()["temp1"];
//        d->temp2 = map[key].toMap()["temp2"];
//        d->details = map[key].toMap()["stateDetailed"];
//        d->state1 = map[key].toMap()["state1"];
//        d->state2 = map[key].toMap()["state2"];
//        d->cityName = map[key].toMap()["cityname"];
//        d->quName = map[key].toMap()["quName"];
//        p_d->city_id_map[] = d;
        QMap<QString,QVariant> m = map[key].toMap()["cities"].toMap();
        QStringList l = m.keys();
        foreach(QString key,l)
        {
            d = new WeatherData;
            d->pyName = m[key].toMap()["pyName"].toString();
            d->windState = m[key].toMap()["pyName"].toString();
            d->temp1 = m[key].toMap()["temp1"].toInt();
            d->temp2 = m[key].toMap()["temp2"].toInt();
            d->details = m[key].toMap()["stateDetailed"].toString();
            d->state1 = m[key].toMap()["state1"].toInt();
            d->state2 = m[key].toMap()["state2"].toInt();
            d->cityName = m[key].toMap()["cityname"].toString();
            d->quName = m[key].toMap()["quName"].toString();
            d->centerName = m[key].toMap()["centername"].toString();
            d->temNow = m[key].toMap()["temNow"].toInt();
            d->windDir = m[key].toMap()["windDir"].toString();
            d->windPower = m[key].toMap()["windPower"].toString();
            d->humidity = m[key].toMap()["humidity"].toString();
            d->time = m[key].toMap()["time"].toString();
            d->url = m[key].toMap()["url"].toInt();
            p_d->city_id_map[d->url] = d;
            p_d->pyname_map[d->pyName] = d;
            p_d->quname_map[d->quName] = d;
        }
    }

    if(city_id_url.contains(p_d->city_id))
    {
        int url = city_id_url[p_d->city_id];
        if(p_d->city_id_map.contains(url))
        {
            ui->temperature->setText(QString::number(p_d->city_id_map[url]->temNow)+"°C");
            ui->region->setText(p_d->city_id_map[url]->centerName);
            ui->weather->setText(p_d->city_id_map[url]->details+ " " + p_d->city_id_map[url]->windDir);
            ui->air->setText(tr("Hunmality:") + p_d->city_id_map[url]->humidity);
        }
    }
}

void WeatherView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    p_d->drawWindowEdge(&painter);
    p_d->drawBackground(&painter);
    QStackedWidget::paintEvent(event);
}

bool WeatherView::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==ui->input)
    {
        if(p_d->search->isVisible())
        {
            if(event->type()==QEvent::FocusOut || event->type()==QEvent::FocusAboutToChange || event->type()==QEvent::WindowDeactivate)
                return true;
        }
    }
    return QStackedWidget::eventFilter(watched,event);
}

void WeatherView::moveEvent(QMoveEvent *event)
{
    p_d->updatesearch();
    QStackedWidget::moveEvent(event);
}

void WeatherView::citySelected(QListWidgetItem *item)
{
    if(item)
    {
        p_d->search->setVisible(false);
        if(ui->first->text().isEmpty())
        {
            ui->first->setText(item->text());
            return ;
        }
        if(ui->second->text().isEmpty())
        {
            ui->second->setText(item->text());
            return ;
        }
        if(ui->third->text().isEmpty())
        {
            ui->third->setText(item->text());
            ui->local->setPlaceholderText(tr("Only three cities available"));
            ui->local->setEnabled(false);
            return ;
        }
    }
}

void WeatherView::on_setting_clicked()
{
    p_d->animationEnable = false;
    WMAnimation::turn_with_stacked(this,WMAnimation::LeftToRight,1500,0,1);
}

void WeatherView::on_finish_clicked()
{
    p_d->animationEnable = true;
    WMAnimation::turn_with_stacked(this,WMAnimation::LeftToRight,1500,1,0);
}

void WeatherView::on_input_textChanged(const QString &arg1)
{
    p_d->inputChanged(arg1);
}

WeatherSearchView::WeatherSearchView(QWidget *parent)
    :QListWidget(0),
      p(parent)
{

}

WeatherSearchView::~WeatherSearchView()
{

}

void WeatherSearchView::keyPressEvent(QKeyEvent *event)
{
    if(p)
    {
        QKeyEvent *e =new QKeyEvent(event->type(),event->key(),event->modifiers(),event->text(),event->isAutoRepeat(),event->count());
        QApplication::postEvent(p,e);
    }
    QListWidget::keyPressEvent(event);
}

void WeatherSearchView::focusOutEvent(QFocusEvent *event)
{
    setVisible(false);
    QListWidget::focusOutEvent(event);
}

void WeatherView::on_first_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
    {
        ui->first->setText(ui->second->text());
        ui->second->setText(ui->third->text());
        ui->input->setEnabled(true);
        ui->input->setPlaceholderText(tr("Input the name of city"));
    }
}

void WeatherView::on_second_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
    {
        ui->second->setText(ui->third->text());
        ui->input->setEnabled(true);
        ui->input->setPlaceholderText(tr("Input the name of city"));
    }
}

void WeatherView::on_third_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
    {
        ui->input->setEnabled(true);
        ui->input->setPlaceholderText(tr("Input the name of city"));
    }
}
