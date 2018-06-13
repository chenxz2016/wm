#ifndef HOTKEYSETTING_H
#define HOTKEYSETTING_H

#include <QWidget>

namespace Ui {
class HotkeySetting;
}

class HotkeySetting : public QWidget
{
    Q_OBJECT

public:
    explicit HotkeySetting(QWidget *parent = 0);
    ~HotkeySetting();

private:
    Ui::HotkeySetting *ui;
};

#endif // HOTKEYSETTING_H
