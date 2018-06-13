#ifndef REMOTEDESKTOPSETTING_H
#define REMOTEDESKTOPSETTING_H

#include <QWidget>

namespace Ui {
class RemoteDesktopSetting;
}

class RemoteDesktopSetting : public QWidget
{
    Q_OBJECT

public:
    explicit RemoteDesktopSetting(QWidget *parent = 0);
    ~RemoteDesktopSetting();

private:
    Ui::RemoteDesktopSetting *ui;
};

#endif // REMOTEDESKTOPSETTING_H
