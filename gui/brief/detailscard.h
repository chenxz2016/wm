#ifndef DETAILSCARD_H
#define DETAILSCARD_H

#include <QWidget>

namespace Ui {
class DetailsCard;
}


class DetailsCard : public QWidget
{
    Q_OBJECT

public:
    explicit DetailsCard(QWidget *parent = 0);
    ~DetailsCard();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    Ui::DetailsCard *ui;
    class DetailsCardPrivate *p_d;
    friend class DetailsCardPrivate;
};

#endif // DETAILSCARD_H
