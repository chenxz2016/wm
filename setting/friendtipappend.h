#ifndef FRIENDTIPAPPEND_H
#define FRIENDTIPAPPEND_H

#include <QWidget>

namespace Ui {
class FriendTipAppend;
}

class FriendTipAppend : public QWidget
{
    Q_OBJECT

public:
    explicit FriendTipAppend(QWidget *parent = 0);
    ~FriendTipAppend();

private:
    Ui::FriendTipAppend *ui;
};

#endif // FRIENDTIPAPPEND_H
