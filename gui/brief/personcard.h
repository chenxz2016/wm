#ifndef PERSONCARD_H
#define PERSONCARD_H

#include <QWidget>

namespace Ui {
class PersonCard;
class ShortIntroduction;
}

class ShortIntroduction : public QWidget
{
    Q_OBJECT
public:
    ShortIntroduction(QWidget *parent = 0);
    ~ShortIntroduction();

    void paintEvent(QPaintEvent *event);
private:
    Ui::ShortIntroduction *ui;
    class ShortIntroductionPrivate *p_d;
};

class PersonCard : public QWidget
{
    Q_OBJECT

public:
    explicit PersonCard(QWidget *parent = 0);
    ~PersonCard();

protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::PersonCard *ui;
    class PersonCardPrivate *p_d;
    friend class PersonCardPrivate;
};

#endif // PERSONCARD_H
