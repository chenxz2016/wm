#ifndef TALKWARNTIP_H
#define TALKWARNTIP_H

#include <QWidget>

namespace Ui
{
class TalkWarnTip;
}

class TalkWarnTip : public QWidget
{
    Q_OBJECT
public:
    TalkWarnTip(QWidget *parent);
    ~TalkWarnTip();

    void setWarnText(const QString &text);
    QString warnText()const;

    void pop(const QSize &size,const QString &warning = "");
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::TalkWarnTip *ui;
    QTimer *timer;
};

#endif // TALKWARNTIP_H
