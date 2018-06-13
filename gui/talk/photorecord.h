#ifndef PHOTORECORD_H
#define PHOTORECORD_H

#include <QWidget>

class PhotoRecord : public QWidget
{
    Q_OBJECT
public:
    explicit PhotoRecord(QWidget *parent = 0);
    ~PhotoRecord();

    int count()const;
    void setMaxCount(int count);

    void setPhotoSize(const QSize &size);
    QSize photoSize()const;
public slots:
    void insertPhoto(const QString &date,const QPixmap &photo,const QString &info);
    void insertPhoto(const QString &date,const QString &photo,const QString &info);
signals:
    void photoClicked(const QPixmap &photo);
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
private:
    class PhotoRecordPrivate *p_d;
};

#endif // PHOTORECORD_H
