#ifndef MESSAGERECORD_H
#define MESSAGERECORD_H

#include <QWidget>

namespace Ui {
class MessageRecord;
}

class MessageRecord : public QWidget
{
    Q_OBJECT

public:
    explicit MessageRecord(QWidget *parent = 0);
    ~MessageRecord();

private slots:
    void on_all_toggled(bool checked);

    void on_photo_toggled(bool checked);

    void on_file_toggled(bool checked);

private:
    Ui::MessageRecord *ui;
    class MessageRecordPrivate *p_d;
    friend class MessageRecordPrivate;
};

#endif // MESSAGERECORD_H
