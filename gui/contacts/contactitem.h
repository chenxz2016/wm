#ifndef CONTACTITEM_H
#define CONTACTITEM_H

#include <QWidget>

namespace Ui {
class ContactItem;
}

class ContactItem : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool selectEnlarge READ selectEnlarge WRITE setSelectEnlarge)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(QSize iconEnlargeSize READ iconEnlargeSize WRITE setIconEnlargeSize)
public:
    explicit ContactItem(QWidget *parent = 0);
    ~ContactItem();

    bool selectEnlarge()const;
    void setSelectEnlarge(bool enlarge);

    QSize iconSize()const;
    void setIconSize(const QSize &size);

    QSize iconEnlargeSize()const;
    void setIconEnlargeSize(const QSize &size);
protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::ContactItem *ui;
    class ContactItemPrivate *p_d;
};

#endif // CONTACTITEM_H
