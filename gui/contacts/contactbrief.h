#ifndef CONTACTBRIEF_H
#define CONTACTBRIEF_H

#include <QWidget>

namespace Ui {
class ContactBrief;
}

class ContactBrief : public QWidget
{
    Q_OBJECT

public:
    explicit ContactBrief(QWidget *parent = 0);
    ~ContactBrief();

private:
    Ui::ContactBrief *ui;
};

#endif // CONTACTBRIEF_H
