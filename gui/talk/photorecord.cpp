#include "photorecord.h"

#include <QDebug>
#include <QMap>
#include <QMouseEvent>
#include <QPainter>
#include <photoviewer.h>


class PhotoKey
{
public:
    PhotoKey(const QString &d)
        :date(d)
    {}
    PhotoKey(const PhotoKey &key)
    {
        date = key.date;
        rect = key.rect;
    }
    void operator=(const PhotoKey &key)
    {
        date = key.date;
        rect = key.rect;
    }
    bool operator!=(const PhotoKey &key)const
    {
        if(date!=key.date)
            return true;
        return false;
    }
    bool operator==(const PhotoKey &key)const
    {
        if(date==key.date)
            return true;
        return false;
    }
    bool operator<(const PhotoKey &key)const
    {
        if(date<key.date)
            return true;
        return false;
    }
    QString date;
    QRect rect;
};


struct PhotoInfo
{
    PhotoInfo(const QString &i,const QPixmap &p)
        :photo(p)
        ,info(i)
    {}
    PhotoInfo()
    {}
    PhotoInfo(const PhotoInfo &i)
    {
        info = i.info;
        photo = i.photo;
        rect = i.rect;
    }
    bool operator==(const PhotoInfo &i)const
    {
        if(info==i.info)
            return true;
        return false;
    }
    QPixmap photo;
    QString info;
    QRect rect;
};

typedef QList<PhotoInfo *> PhotoValues;

class PhotoRecordPrivate
{
public:
    PhotoRecordPrivate(PhotoRecord *p = 0)
        :photoSize(48,48)
        ,leftSpace(10)
        ,rightSpace(10)
        ,photoBorderColor(Qt::white)
        ,photoBorderPressedColor(Qt::blue)
        ,photoBorderHoverColor(Qt::blue)
        ,photoBorder(2)
        ,row(3)
        ,dateWidth(64)
        ,dateHeight(24)
        ,parent(p)
    {}
    ~PhotoRecordPrivate()
    {
        QList<PhotoKey> l = map.keys();
        foreach(PhotoKey key,l)
        {
            PhotoValues values = map[key];
            foreach(PhotoInfo *i,values)
                delete i;
        }
    }

    void drawPhotoDate(const PhotoKey &key,QPainter *painter);
    void drawPhotoItem(QPainter *painter);
    void mousePressedEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoublePressedEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void updatePhotoItem();

    QMap<PhotoKey,PhotoValues> map;
    int maxCount;
    QSize photoSize;
    int leftSpace;
    int rightSpace;
    QColor photoBorderColor;
    QColor photoBorderHoverColor;
    QColor photoBorderPressedColor;
    int photoBorder;
    int photoBorderHover;
    int photoBorderPressed;
    int row;
    int dateWidth;
    int dateHeight;

    PhotoInfo selected;
    PhotoInfo hovered;

    PhotoRecord *parent;
};

#define WM_TEST

PhotoRecord::PhotoRecord(QWidget *parent) : QWidget(parent)
{
    p_d = new PhotoRecordPrivate(this);
    resize(320,640);

#ifdef WM_TEST
    insertPhoto(QString("2017/12/21"),QString("G:\\qt_pro\\photos\\1 (1).jpg"),QString("G:\\qt_pro\\photos\\1 (1).jpg"));
    insertPhoto(QString("2017/12/21"),QString("G:\\qt_pro\\photos\\1 (2).jpg"),QString("G:\\qt_pro\\photos\\1 (2).jpg"));
    insertPhoto(QString("2017/12/21"),QString("G:\\qt_pro\\photos\\1 (3).jpg"),QString("G:\\qt_pro\\photos\\1 (3).jpg"));
    insertPhoto(QString("2017/12/21"),QString("G:\\qt_pro\\photos\\1 (4).jpg"),QString("G:\\qt_pro\\photos\\1 (4).jpg"));
    insertPhoto(QString("2017/12/21"),QString("G:\\qt_pro\\photos\\1 (5).jpg"),QString("G:\\qt_pro\\photos\\1 (5).jpg"));
    insertPhoto(QString("2017/12/22"),QString("G:\\qt_pro\\photos\\1 (6).jpg"),QString("G:\\qt_pro\\photos\\1 (6).jpg"));
    insertPhoto(QString("2017/12/22"),QString("G:\\qt_pro\\photos\\1 (7).jpg"),QString("G:\\qt_pro\\photos\\1 (7).jpg"));
    insertPhoto(QString("2017/12/23"),QString("G:\\qt_pro\\photos\\1 (8).jpg"),QString("G:\\qt_pro\\photos\\1 (8).jpg"));
    insertPhoto(QString("2017/12/20"),QString("G:\\qt_pro\\photos\\1 (9).jpg"),QString("G:\\qt_pro\\photos\\1 (9).jpg"));
    insertPhoto(QString("2017/12/20"),QString("G:\\qt_pro\\photos\\1 (10).jpg"),QString("G:\\qt_pro\\photos\\1 (10).jpg"));
    insertPhoto(QString("2017/12/20"),QString("G:\\qt_pro\\photos\\1 (11).jpg"),QString("G:\\qt_pro\\photos\\1 (11).jpg"));
    insertPhoto(QString("2017/12/20"),QString("G:\\qt_pro\\photos\\1 (12).jpg"),QString("G:\\qt_pro\\photos\\1 (12).jpg"));
    insertPhoto(QString("2017/12/20"),QString("G:\\qt_pro\\photos\\1 (13).jpg"),QString("G:\\qt_pro\\photos\\1 (13).jpg"));
    insertPhoto(QString("2017/12/20"),QString("G:\\qt_pro\\photos\\1 (14).jpg"),QString("G:\\qt_pro\\photos\\1 (14).jpg"));
    insertPhoto(QString("2017/12/20"),QString("G:\\qt_pro\\photos\\1 (15).jpg"),QString("G:\\qt_pro\\photos\\1 (15).jpg"));
    insertPhoto(QString("2017/12/20"),QString("G:\\qt_pro\\photos\\1 (16).jpg"),QString("G:\\qt_pro\\photos\\1 (16).jpg"));
    insertPhoto(QString("2017/12/22"),QString("G:\\qt_pro\\photos\\1 (17).jpg"),QString("G:\\qt_pro\\photos\\1 (17).jpg"));
    insertPhoto(QString("2017/12/22"),QString("G:\\qt_pro\\photos\\1 (18).jpg"),QString("G:\\qt_pro\\photos\\1 (18).jpg"));


    insertPhoto(QString("2017/12/19"),QString("G:\\qt_pro\\photos\\1 (19).jpg"),QString("G:\\qt_pro\\photos\\1 (19).jpg"));
    insertPhoto(QString("2017/12/18"),QString("G:\\qt_pro\\photos\\1 (20).jpg"),QString("G:\\qt_pro\\photos\\1 (20).jpg"));
    insertPhoto(QString("2017/12/17"),QString("G:\\qt_pro\\photos\\1 (21).jpg"),QString("G:\\qt_pro\\photos\\1 (21).jpg"));
#endif
}

PhotoRecord::~PhotoRecord()
{
    delete p_d;
}

int PhotoRecord::count() const
{
    return p_d->maxCount;
}

void PhotoRecord::setMaxCount(int count)
{
    p_d->maxCount = count;
}

void PhotoRecord::setPhotoSize(const QSize &size)
{
    p_d->photoSize =size;
    update();
}

QSize PhotoRecord::photoSize() const
{
    return p_d->photoSize;
}

void PhotoRecord::insertPhoto(const QString &date, const QPixmap &photo,const QString &info)
{
    PhotoInfo *i = new PhotoInfo(info,photo);
    PhotoValues &values = p_d->map[PhotoKey(date)];
    values.append(i);
    p_d->updatePhotoItem();
}

void PhotoRecord::insertPhoto(const QString &date, const QString &photo,const QString &info)
{
    PhotoInfo *i = new PhotoInfo(info,photo);
    PhotoValues &values = p_d->map[PhotoKey(date)];
    values.append(i);
    p_d->updatePhotoItem();
}

void PhotoRecord::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    p_d->drawPhotoItem(&painter);
    QWidget::paintEvent(event);
}

void PhotoRecord::resizeEvent(QResizeEvent *event)
{
    p_d->updatePhotoItem();
    QWidget::resizeEvent(event);
}

void PhotoRecord::mousePressEvent(QMouseEvent *event)
{
    p_d->mousePressedEvent(event);
    QWidget::mousePressEvent(event);
}

void PhotoRecord::mouseMoveEvent(QMouseEvent *event)
{
    p_d->mouseMoveEvent(event);
    QWidget::mouseMoveEvent(event);
}

void PhotoRecord::mouseReleaseEvent(QMouseEvent *event)
{
    p_d->mouseReleaseEvent(event);
    QWidget::mouseReleaseEvent(event);
}

void PhotoRecord::mouseDoubleClickEvent(QMouseEvent *event)
{
    p_d->mouseDoublePressedEvent(event);
    QWidget::mouseDoubleClickEvent(event);
}

void PhotoRecordPrivate::drawPhotoDate(const PhotoKey &key,QPainter *painter)
{
    painter->save();
    painter->drawText(key.rect,Qt::AlignCenter,key.date);
    painter->restore();
}

void PhotoRecordPrivate::drawPhotoItem(QPainter *painter)
{
    painter->save();
    QList<PhotoKey> list = map.keys();
    foreach(PhotoKey key,list)
    {
        drawPhotoDate(key,painter);
        QList<PhotoInfo*> l = map.value(key);
        foreach(PhotoInfo *i,l)
        {
            if(selected==*i)
                painter->fillRect(i->rect,photoBorderPressedColor);
            else if(hovered==*i)
                painter->fillRect(i->rect,photoBorderHoverColor);
            else
                painter->fillRect(i->rect,photoBorderColor);
            QRect r;
            r.setLeft(i->rect.left()+photoBorder);
            r.setRight(i->rect.right()-photoBorder);
            r.setTop(i->rect.top()+photoBorder);
            r.setBottom(i->rect.bottom()-photoBorder);
            painter->drawPixmap(r,i->photo.scaled(photoSize));
        }
    }
    painter->restore();
}

void PhotoRecordPrivate::mousePressedEvent(QMouseEvent *event)
{
    QList<PhotoKey> list = map.keys();
    foreach(PhotoKey key,list)
    {
        QList<PhotoInfo*> l = map.value(key);
        foreach(PhotoInfo *i,l)
        {
            if(i->rect.contains(event->pos()))
            {
                selected = *i;
                parent->repaint();
                return ;
            }
        }
    }
}

void PhotoRecordPrivate::mouseMoveEvent(QMouseEvent *event)
{
    QList<PhotoKey> list = map.keys();
    foreach(PhotoKey key,list)
    {
        QList<PhotoInfo*> l = map.value(key);
        foreach(PhotoInfo *i,l)
        {
            if(i->rect.contains(event->pos()))
            {
                selected = *i;
                parent->repaint();
                return ;
            }
        }
    }
}

void PhotoRecordPrivate::mouseDoublePressedEvent(QMouseEvent *event)
{
    QList<PhotoKey> list = map.keys();
    foreach(PhotoKey key,list)
    {
        QList<PhotoInfo*> l = map.value(key);
        foreach(PhotoInfo *i,l)
        {
            if(i->rect.contains(event->pos()))
            {
                emit parent->photoClicked(i->photo);
                QList<QPixmap> ll;
                ll.append(i->photo);
                PhotoViewer::viewPhotos(ll);
                return ;
            }
        }
    }
}

void PhotoRecordPrivate::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void PhotoRecordPrivate::updatePhotoItem()
{
    if(!parent)
        return ;

    QMap<PhotoKey,PhotoValues> m;
    int h = 0;
    QList<PhotoKey> list = map.keys();
    foreach(PhotoKey key,list)
    {
        QList<PhotoInfo*> l = map[key];
        if(!l.count())
            continue;

        key.rect = QRect(leftSpace,h,dateWidth,dateHeight);
        h+= dateHeight;
        int ridx = 0;
        foreach(PhotoInfo *i,l)
        {
            i->rect = QRect(QPoint(leftSpace+ridx*photoSize.width(),h),photoSize);
            ridx++;
            if(ridx==row)
            {
                ridx = 0;
                h+=photoSize.height();
            }
//            qDebug() << "rect:" << i->rect;
        }

        h+= photoSize.height();

        m[key] = l;
    }
    map = m;
}
