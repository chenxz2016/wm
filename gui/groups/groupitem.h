#ifndef GROUPITEM_H
#define GROUPITEM_H

#include <QWidget>

namespace Ui {
class GroupItem;
class MultiTalkItem;
}

class GroupItem : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool mailLinkEnable READ mailLinkEnable WRITE setMailLinkEnable)
    Q_PROPERTY(bool selectEnlarge READ selectEnlarge WRITE setSelectEnlarge)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(QSize iconEnlargeSize READ iconEnlargeSize WRITE setIconEnlargeSize)
public:
    explicit GroupItem(QWidget *parent = 0);
    ~GroupItem();

    bool mailLinkEnable()const;
    void setMailLinkEnable(bool enable);

    bool selectEnlarge()const;
    void setSelectEnlarge(bool enlarge);

    QSize iconSize()const;
    void setIconSize(const QSize &size);

    QSize iconEnlargeSize()const;
    void setIconEnlargeSize(const QSize &size);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
private:
    Ui::GroupItem *ui;
    class GroupItemPrivate *p_d;
};

class MultiTalkItem : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool selectEnlarge READ selectEnlarge WRITE setSelectEnlarge)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(QSize iconEnlargeSize READ iconEnlargeSize WRITE setIconEnlargeSize)
public:
    explicit MultiTalkItem(QWidget *parent = 0);
    ~MultiTalkItem();

    bool selectEnlarge()const;
    void setSelectEnlarge(bool enlarge);

    QSize iconSize()const;
    void setIconSize(const QSize &size);

    QSize iconEnlargeSize()const;
    void setIconEnlargeSize(const QSize &size);
protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::MultiTalkItem *ui;
    class MultiTalkItemPrivate *p_d;
};


#endif // GROUPITEM_H
