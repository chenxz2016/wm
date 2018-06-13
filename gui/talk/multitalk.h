#ifndef MULTITALK_H
#define MULTITALK_H

#include <QWidget>

namespace Ui{
class MultiTalk;
}

class AbstractMessageItem;

class MultiTalk : public QWidget
{
    Q_OBJECT
public:
    explicit MultiTalk(QWidget *parent = 0);
    ~MultiTalk();

    void appendItem(AbstractMessageItem *item);
    void appendItems(const QList<AbstractMessageItem *> &items);

    void prependItem(AbstractMessageItem *item);
    void prependItems(const QList<AbstractMessageItem *> &items);

    void removeItem(AbstractMessageItem *item);

    void setMaxCount(int count);
    int maxCount()const;

    void appendMember(const QVariant &member);
    void appendMembers(const QList<QVariant> &members);
    void removeMember(const QVariant &member);

    void updateMessageItems();
signals:

    void headClicked(QString);
public slots:

protected:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::MultiTalk *ui;
    class MultiTalkPrivate *p_d;
    friend class MultiTalkPrivate;
};

#endif // MULTITALK_H
