#ifndef TOOLBARACTION_H
#define TOOLBARACTION_H

#include <QWidget>

class QActoion;

class ToolBarAction : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString iconPath READ iconPath WRITE setIconPath)
    Q_PROPERTY(QPixmap icon READ icon WRITE setIcon)
    Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap)
public:
    explicit ToolBarAction(QWidget *parent = 0);
    ~ToolBarAction();

    QString iconPath()const;
    void setIconPath(const QString &path);

    QPixmap icon()const;
    void setIcon(const QPixmap &pixmap);

    QPixmap pixmap()const;
    void setPixmap(const QPixmap &pixmap);
signals:
    void trigger();
    void clicked();
    void pressed();
    void indicatorClick();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void resizeEvent(QResizeEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
private:
    class ToolBarActionPrivate *p_d;
};

#endif // TOOLBARACTION_H
