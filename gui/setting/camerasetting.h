#ifndef CAMERASETTING_H
#define CAMERASETTING_H

#include <QWidget>

namespace Ui {
class CameraSetting;
}

class CameraSetting : public QWidget
{
    Q_OBJECT

public:
    explicit CameraSetting(QWidget *parent = 0);
    ~CameraSetting();

private:
    Ui::CameraSetting *ui;
};

#endif // CAMERASETTING_H
