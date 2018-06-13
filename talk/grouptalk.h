#ifndef GROUPTALK_H
#define GROUPTALK_H

#include <QWidget>

namespace Ui {
class GroupTalk;
}

class AbstractMessageItem;

class GroupTalk : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int maxCount READ maxCount WRITE setMaxCount)
public:
    explicit GroupTalk(QWidget *parent = 0);
    ~GroupTalk();

    void appendItem(AbstractMessageItem *item);
    void appendItems(const QList<AbstractMessageItem *> &items);

    void prependItem(AbstractMessageItem *item);
    void prependItems(const QList<AbstractMessageItem *> &items);

    void removeItem(AbstractMessageItem *item);

    void setMaxCount(int count);
    int maxCount()const;

    void showWarning(const QString &warning);

    void updateMessageItems();
signals:
    void headClicked(QString);
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::GroupTalk *ui;
    class GroupTalkPrivate *p_d;
    friend class GroupTalkPrivate;
};

#endif // GROUPTALK_H
