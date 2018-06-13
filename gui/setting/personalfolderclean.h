#ifndef PERSONALFOLDERCLEAN_H
#define PERSONALFOLDERCLEAN_H

#include <QWidget>

namespace Ui {
class PersonalFolderClean;
}

class PersonalFolderClean : public QWidget
{
    Q_OBJECT

public:
    explicit PersonalFolderClean(QWidget *parent = 0);
    ~PersonalFolderClean();

private:
    Ui::PersonalFolderClean *ui;
};

#endif // PERSONALFOLDERCLEAN_H
