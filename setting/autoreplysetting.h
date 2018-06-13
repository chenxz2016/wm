#ifndef AUTOREPLYSETTING_H
#define AUTOREPLYSETTING_H

#include <QWidget>

namespace Ui {
class AutoReplySetting;
}

class AutoReplySetting : public QWidget
{
    Q_OBJECT

public:
    explicit AutoReplySetting(QWidget *parent = 0);
    ~AutoReplySetting();

private:
    Ui::AutoReplySetting *ui;
};

#endif // AUTOREPLYSETTING_H
