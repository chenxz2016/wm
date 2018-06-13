#ifndef BRIEFCARD_H
#define BRIEFCARD_H

#include <QWidget>

namespace Ui {
class BriefCard;
}

class BriefCard : public QWidget
{
    Q_OBJECT
public:
    explicit BriefCard(QWidget *parent = 0);
    ~BriefCard();

    void setBriefData(const QVariant &data);
signals:
    void requestHide();
public slots:
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_name_clicked();

private:
    Ui::BriefCard *ui;
    class BriefCardPrivate *p_d;
    friend class BriefCardPrivate;
};

#endif // BRIEFCARD_H
