#ifndef ENSHRIEN_H
#define ENSHRIEN_H

#include <QWidget>

namespace Ui {
class Enshrien;
}

class Enshrien : public QWidget
{
    Q_OBJECT

public:
    explicit Enshrien(QWidget *parent = 0);
    ~Enshrien();

private:
    Ui::Enshrien *ui;
};

#endif // ENSHRIEN_H
