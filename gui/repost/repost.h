#ifndef REPOST_H
#define REPOST_H

#include <QWidget>

namespace Ui {
class Repost;
}

class Repost : public QWidget
{
    Q_OBJECT

public:
    explicit Repost(QWidget *parent = 0);
    ~Repost();

private:
    Ui::Repost *ui;
};

#endif // REPOST_H
