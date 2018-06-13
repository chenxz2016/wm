#ifndef VIEWITEM_H
#define VIEWITEM_H

#include <QWidget>

namespace Ui {
class ViewItem;
}

class ViewItem : public QWidget
{
    Q_OBJECT
//    Q_PROPERTY(bool iconToolTipEnable READ iconToolTipEnable WRITE setIconToolTipEnable)

public:
    explicit ViewItem(QWidget *parent = 0);
    ~ViewItem();

private:
    Ui::ViewItem *ui;
};

#endif // VIEWITEM_H
