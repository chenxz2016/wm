#include "photoviewer.h"

#include "ui_photoviewer.h"
#include "windowimpl.h"

#include <QDateTime>
#include <QDebug>
#include <QFileDialog>
#include <QGraphicsOpacityEffect>
#include <QMouseEvent>
#include <QPainter>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QTimer>

#define PI          3.1415926


class PhotoViewerPrivate : public WindowImpl
{
public:
    PhotoViewerPrivate(PhotoViewer *parent)
        :WindowImpl(parent)
        ,p(parent)
        ,angle(0)
        ,scaleFactor(1.0)
        ,mouseMove(false)
    {}

    void drawBackground(QPainter *painter)
    {
        if(!p)
            return ;

        painter->fillRect(p->rect(),bgColor);
    }

    void mouseMoveEvent(QMouseEvent *event)
    {
        mouseMove = true;
        WindowImpl::mouseMoveEvent(event);
        if(Qt::ArrowCursor==p->cursor().shape())
            p->setCursor(Qt::OpenHandCursor);

        if(event->pos().x()>0 && event->pos().x()<=80)
        {
            if(!p->ui->left->isVisible())
                animation_show(p->ui->left);
        }
        else
        {
            if(p->ui->left->isVisible())
                animation_hide(p->ui->left);
        }

        if(event->pos().x()<=p->width() && event->pos().x()>=(p->width()-80))
        {
            if(!p->ui->right->isVisible())
                animation_show(p->ui->right);
        }
        else
        {
            if(p->ui->right->isVisible())
                animation_hide(p->ui->right);
        }

        if(event->pos().y()<=p->height() && event->pos().y()>=(p->height()-80))
        {
            if(!p->ui->tool->isVisible())
                animation_show(p->ui->tool);
        }
        else
        {
            if(p->ui->tool->isVisible())
                animation_hide(p->ui->tool);
        }
    }

    void mousePressEvent(QMouseEvent *event)
    {
        mouseMove = false;
        WindowImpl::mousePressEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event)
    {
        Q_UNUSED(event)

        if(!mouseMove)
        {
            mouseMove = false;
            animation_close(p);
        }
        WindowImpl::mouseReleaseEvent(event);
    }

    void animation_close(QWidget *widget)
    {
        QRect r = widget->geometry();
        QPropertyAnimation *moveAnimation = new QPropertyAnimation(widget,"geometry");
        moveAnimation->setStartValue(r);
        r = QRect(r.x(),r.y()-120,r.width(),r.height());
        moveAnimation->setEndValue(r);
        moveAnimation->setDuration(200);

        QPropertyAnimation *closeAnimation = new QPropertyAnimation(widget,"windowOpacity");
        closeAnimation->setStartValue(1.0);
        closeAnimation->setEndValue(0);
        closeAnimation->setDuration(200);

        QParallelAnimationGroup *group = new QParallelAnimationGroup;
        group->addAnimation(moveAnimation);
        group->addAnimation(closeAnimation);

        QObject::connect(group,SIGNAL(finished()),widget,SLOT(close()));
        group->start();
    }

    void animation_hide(QWidget *widget)
    {
        if(!widget)
            return ;

        if(!hideMap.contains(widget))
        {
            QGraphicsEffect *gof = widget->graphicsEffect();
            QPropertyAnimation *animation = new QPropertyAnimation(gof,"opacity",widget);
            hideMap[widget] = animation;
            animation->setStartValue(1.0);
            animation->setEndValue(0);
            hideMap[widget]->setDuration(1000);
            QObject::connect(animation,SIGNAL(finished()),widget,SLOT(hide()));
        }

        hideMap[widget]->start();
    }

    void animation_show(QWidget *widget)
    {
        if(!widget)
            return ;

        if(!showMap.contains(widget))
        {
            QGraphicsEffect *gof = widget->graphicsEffect();
            QPropertyAnimation *animation = new QPropertyAnimation(gof,"opacity",widget);
            showMap[widget] = animation;
            showMap[widget]->setDuration(1000);
            animation->setStartValue(0);
            animation->setEndValue(1.0);
            QObject::connect(animation,SIGNAL(finished()),widget,SLOT(show()));
        }

        showMap[widget]->start();
        widget->setVisible(true);
    }

    void stop_hide_animation(QWidget *widget)
    {
        if(widget || !hideMap.contains(widget))
            return ;

        hideMap[widget]->stop();
    }

    void delay_hide(QWidget *widget,int msec)
    {
        if(!widget)
            return ;

        if(!timerMap.contains(widget))
        {
            QTimer *timer = new QTimer;
            timerMap[widget] = timer;
            timer->setInterval(msec);
            timer->setSingleShot(true);
            QObject::connect(timer,SIGNAL(timeout()),widget,SLOT(hide()));
        }

        timerMap[widget]->start();
    }

    void cancel_delay_hide(QWidget *widget)
    {
        if(!widget || !timerMap.contains(widget))
            return ;

        timerMap[widget]->stop();
    }

    PhotoViewer *p;
    QPixmap currentPixmap;
    QList<QPixmap> list;
    QSize orignalSize;
    QSize size;

    QMap<QWidget *,QPropertyAnimation *> showMap;
    QMap<QWidget *,QPropertyAnimation *> hideMap;

    double angle;
    double scaleFactor;

    bool mouseMove;
    QMap<QWidget *,QTimer *> timerMap;
};

#define WM_TEST 1

PhotoViewer::PhotoViewer(QWidget *parent)
    : QWidget(parent)
    ,ui(new Ui::PhotoViewer)
{
    ui->setupUi(this);
    ui->tool->installEventFilter(this);

    p_d = new PhotoViewerPrivate(this);
    p_d->bgColor = QColor(0,0,0,125);

    QGraphicsOpacityEffect *gof = new QGraphicsOpacityEffect(ui->tool);
    ui->tool->setGraphicsEffect(gof);
    ui->tool->hide();
    gof = new QGraphicsOpacityEffect(ui->right);
    ui->right->hide();
    ui->right->setGraphicsEffect(gof);
    gof = new QGraphicsOpacityEffect(ui->left);
    ui->left->setGraphicsEffect(gof);
    ui->left->hide();

    share = new QToolBar(this);
    share->installEventFilter(this);
    share->setObjectName("share");
    share->setStyleSheet("QToolBar#share{background-color:black;}");
    share->addAction(ui->saveToSpace);
    share->addAction(ui->saveToCloud);
    share->addAction(ui->ensherin);
    share->addAction(ui->sendToMobile);
    share->adjustSize();
    share->hide();

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);

//#ifdef WM_TEST
//    appendPhoto(QPixmap("G:\\qt_pro\\photos\\1 (1).jpg"));
//#endif

    setMinimumSize(720,520);
    resize(1280,720);
}

PhotoViewer::~PhotoViewer()
{
    delete p_d;
}

void PhotoViewer::appendPhoto(const QPixmap &photo)
{
    p_d->list.append(photo);
    p_d->currentPixmap = photo;
    update();
}

void PhotoViewer::appendPhotos(const QList<QPixmap> &photos)
{
    if(photos.isEmpty())
        return ;

    p_d->list.append(photos);
    p_d->currentPixmap = photos.first();
    update();
}

void PhotoViewer::viewPhotos(const QList<QPixmap> &list)
{
    PhotoViewer *viewer = new PhotoViewer;
    viewer->appendPhotos(list);
    viewer->show();
}

void PhotoViewer::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    p_d->drawBackground(&painter);

    QRect r;
    QSize pSize = p_d->currentPixmap.size()*p_d->scaleFactor;
    r.setTopLeft(QPoint(-pSize.width()/2,-pSize.height()/2));
    r.setSize(pSize);
    painter.save();
    painter.translate(rect().center());
    painter.rotate(p_d->angle);
    painter.drawPixmap(r,p_d->currentPixmap.scaled(pSize));
    painter.restore();
}

void PhotoViewer::mousePressEvent(QMouseEvent *event)
{
    p_d->mousePressEvent(event);
    QWidget::mousePressEvent(event);
}

void PhotoViewer::mouseMoveEvent(QMouseEvent *event)
{
    p_d->mouseMoveEvent(event);
    QWidget::mouseMoveEvent(event);
}

void PhotoViewer::mouseReleaseEvent(QMouseEvent *event)
{
    p_d->mouseReleaseEvent(event);
    QWidget::mouseReleaseEvent(event);
}

bool PhotoViewer::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==ui->tool)
    {
        QPoint p;
        switch(event->type())
        {
        case QEvent::HoverMove:
            p = ui->tool->mapFromGlobal(QCursor::pos());
            qDebug() << "toool" << event->type();
            if(ui->tool->actionAt(p)==ui->share)
            {
                QRect r = ui->tool->actionGeometry(ui->share);
                QPoint p = ui->tool->mapToParent(r.center());
                QRect sr;
                sr.setTopLeft(QPoint(p.x()-share->width()/2,p.y()-share->height()-ui->tool->height()/2));
                sr.setSize(share->size());
                share->setGeometry(sr);
                share->show();
            }
            else
                p_d->delay_hide(share,1000);
            return false;
        default:
            break;
        }
    }

    if(watched==share)
    {
        switch(event->type())
        {
        case QEvent::Enter:
            p_d->cancel_delay_hide(share);
            return false;
        case QEvent::Leave:
            p_d->delay_hide(share,1000);
            return false;
        default:
            break;
        }
    }

    return QWidget::eventFilter(watched,event);
}

void PhotoViewer::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0)
        on_zoomin_triggered();
    else
        on_zoomout_triggered();

    QWidget::wheelEvent(event);
}

void PhotoViewer::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
}

void PhotoViewer::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
}

void PhotoViewer::on_save_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,"Save As",\
                                 QDir::currentPath()+QString("/wm picture").arg(QDateTime::currentDateTime().toString()),\
                                 "*.jpg *.bmp");
    if(!filename.isEmpty())
        p_d->currentPixmap.save(filename,"PNG");

}

void PhotoViewer::on_openByDefaultViewer_triggered()
{
}

void PhotoViewer::on_zoomin_triggered()
{
    p_d->scaleFactor -= 0.1;

    if(p_d->scaleFactor<0.3)
        p_d->scaleFactor = 0.3;

    if(p_d->scaleFactor == 0.3)
        ui->zoomin->setEnabled(false);
    else
        ui->zoomin->setEnabled(true);

    if(p_d->scaleFactor == 2.0)
        ui->zoomout->setEnabled(false);
    else
        ui->zoomout->setEnabled(true);

    ui->realSize->setEnabled(false);
    if(p_d->scaleFactor!=1.0)
        ui->realSize->setEnabled(true);

    ui->sizeShow->setText(QString("%1%").arg(p_d->scaleFactor*100));

    repaint();
}

void PhotoViewer::on_zoomout_triggered()
{
    p_d->scaleFactor += 0.1;

    if(p_d->scaleFactor>2.0)
        p_d->scaleFactor = 2.0;

    if(p_d->scaleFactor == 0.3)
        ui->zoomin->setEnabled(false);
    else
        ui->zoomin->setEnabled(true);

    if(p_d->scaleFactor == 2.0)
        ui->zoomout->setEnabled(false);
    else
        ui->zoomout->setEnabled(true);

    ui->realSize->setEnabled(false);
    if(p_d->scaleFactor!=1.0)
        ui->realSize->setEnabled(true);

    ui->sizeShow->setText(QString("%1%").arg(p_d->scaleFactor*100));

    repaint();
}

void PhotoViewer::on_realSize_triggered()
{
    p_d->scaleFactor = 1.0;
    ui->sizeShow->setText(QString("%1%").arg(p_d->scaleFactor*100));
    ui->realSize->setEnabled(false);

    repaint();
}

void PhotoViewer::on_fullScreen_triggered()
{
    if(!isMaximized())
    {
        ui->bottom_layout->setContentsMargins(0,0,0,30);
        showMaximized();
    }
    else
    {
        ui->bottom_layout->setContentsMargins(0,0,0,0);
        showNormal();
    }
}

void PhotoViewer::on_turnRight_triggered()
{
    p_d->angle += 90;
    repaint();
}

