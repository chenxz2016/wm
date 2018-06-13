#ifndef GROUPSSHIELDSETTING_H
#define GROUPSSHIELDSETTING_H

#include <QWidget>

namespace Ui {
class GroupsShieldSetting;
}

class GroupsShieldSetting : public QWidget
{
    Q_OBJECT

public:
    explicit GroupsShieldSetting(QWidget *parent = 0);
    ~GroupsShieldSetting();

private:
    Ui::GroupsShieldSetting *ui;
};

#endif // GROUPSSHIELDSETTING_H
