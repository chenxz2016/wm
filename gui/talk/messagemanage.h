#ifndef MESSAGEMANAGE_H
#define MESSAGEMANAGE_H

#include <QWidget>

namespace Ui {
class MessageManage;
}

class MessageManage : public QWidget
{
    Q_OBJECT

public:
    explicit MessageManage(QWidget *parent = 0);
    ~MessageManage();

private:
    Ui::MessageManage *ui;
};

#endif // MESSAGEMANAGE_H
