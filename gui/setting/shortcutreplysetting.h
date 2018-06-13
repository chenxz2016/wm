#ifndef SHORTCUTREPLYSETTING_H
#define SHORTCUTREPLYSETTING_H

#include <QWidget>

namespace Ui {
class ShortcutReplySetting;
}

class ShortcutReplySetting : public QWidget
{
    Q_OBJECT

public:
    explicit ShortcutReplySetting(QWidget *parent = 0);
    ~ShortcutReplySetting();

private:
    Ui::ShortcutReplySetting *ui;
};

#endif // SHORTCUTREPLYSETTING_H
