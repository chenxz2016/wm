#include "notesedit.h"
#include "ui_notesedit.h"

NotesEdit::NotesEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NotesEdit)
{
    ui->setupUi(this);
}

NotesEdit::~NotesEdit()
{
    delete ui;
}
