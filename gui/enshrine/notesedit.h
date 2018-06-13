#ifndef NOTESEDIT_H
#define NOTESEDIT_H

#include <QWidget>

namespace Ui {
class NotesEdit;
}

class NotesEdit : public QWidget
{
    Q_OBJECT

public:
    explicit NotesEdit(QWidget *parent = 0);
    ~NotesEdit();

private:
    Ui::NotesEdit *ui;
};

#endif // NOTESEDIT_H
