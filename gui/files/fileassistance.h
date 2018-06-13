#ifndef FILEASSISTANCE_H
#define FILEASSISTANCE_H

#include <QWidget>

namespace Ui {
class FileAssistance;
}

class FileAssistance : public QWidget
{
    Q_OBJECT

public:
    explicit FileAssistance(QWidget *parent = 0);
    ~FileAssistance();

private:
    Ui::FileAssistance *ui;
};

#endif // FILEASSISTANCE_H
