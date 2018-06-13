#include "shortcutreplysetting.h"
#include "ui_shortcutreplysetting.h"

ShortcutReplySetting::ShortcutReplySetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShortcutReplySetting)
{
    ui->setupUi(this);
}

ShortcutReplySetting::~ShortcutReplySetting()
{
    delete ui;
}
