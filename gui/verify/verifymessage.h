#ifndef VERIFYMESSAGE_H
#define VERIFYMESSAGE_H

#include <QWidget>

namespace Ui {
class VerifyMessage;
}

class VerifyMessage : public QWidget
{
    Q_OBJECT

public:
    explicit VerifyMessage(QWidget *parent = 0);
    ~VerifyMessage();

private:
    Ui::VerifyMessage *ui;
};

#endif // VERIFYMESSAGE_H
