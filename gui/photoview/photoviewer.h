#ifndef PHOTOVIEWER_H
#define PHOTOVIEWER_H

#include <QWidget>

namespace Ui
{
class PhotoViewer;
}

class QToolBar;

class PhotoViewer : public QWidget
{
    Q_OBJECT
public:
    explicit PhotoViewer(QWidget *parent = 0);
    ~PhotoViewer();

    void appendPhoto(const QPixmap &photo);
    void appendPhotos(const QList<QPixmap> &photos);

    static void viewPhotos(const QList<QPixmap> &photos);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void wheelEvent(QWheelEvent *event);
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
private slots:
    void on_save_triggered();

    void on_openByDefaultViewer_triggered();

    void on_zoomin_triggered();

    void on_zoomout_triggered();

    void on_realSize_triggered();

    void on_fullScreen_triggered();

    void on_turnRight_triggered();
private:
    friend class PhotoViewerPrivate;
    class PhotoViewerPrivate *p_d;
    Ui::PhotoViewer *ui;
    QToolBar *share;
};

#endif // PHOTOVIEWER_H
