#ifndef AUTOREPLYAPPEND_H
#define AUTOREPLYAPPEND_H

#include <QWidget>

namespace Ui {
class AutoReplyAppend;
}

class AutoReplyAppend : public QWidget
{
    Q_OBJECT

public:
    explicit AutoReplyAppend(QWidget *parent = 0);
    ~AutoReplyAppend();

private:
    Ui::AutoReplyAppend *ui;
};

#endif // AUTOREPLYAPPEND_H
