#ifndef VIDEOCALLWARNING_H
#define VIDEOCALLWARNING_H

#include <QWidget>

namespace Ui {
class VideoCallWarning;
}

class VideoCallWarning : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString warning READ warning WRITE setWarning)
public:
    explicit VideoCallWarning(QWidget *parent = 0);
    ~VideoCallWarning();

    QString warning()const;
    void setWarning(const QString &warning);
private:
    Ui::VideoCallWarning *ui;
};

#endif // VIDEOCALLWARNING_H
