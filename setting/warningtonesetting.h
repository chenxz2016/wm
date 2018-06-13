#ifndef WARNINGTONESETTING_H
#define WARNINGTONESETTING_H

#include <QWidget>

namespace Ui {
class WarningToneSetting;
}

class WarningToneSetting : public QWidget
{
    Q_OBJECT

public:
    explicit WarningToneSetting(QWidget *parent = 0);
    ~WarningToneSetting();

private:
    Ui::WarningToneSetting *ui;
};

#endif // WARNINGTONESETTING_H
