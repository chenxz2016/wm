#ifndef SESSIONITEM_H
#define SESSIONITEM_H

#include <QDateTime>
#include <QWidget>

namespace Ui {
class SessionItem;
}

class MainWindow;

class SessionItem : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString iconPath READ iconPath WRITE setIconPath)
    Q_PROPERTY(QString describeName READ describeName WRITE setDescribeName)
    Q_PROPERTY(QString lastMessage READ lastMessage WRITE setLastMessage)
    Q_PROPERTY(QDateTime lastTime READ lastTime WRITE setLastTime)
public:
    explicit SessionItem(QWidget *parent = 0);
    ~SessionItem();

    SessionItem *operator =(const SessionItem &item);

    QString iconPath()const;
    void setIconPath(const QString &path);

    QString describeName()const;
    void setDescribeName(const QString &name);

    QString lastMessage()const;
    void setLastMessage(const QString &message);

    QDateTime lastTime()const;
    void setLastTime(const QDateTime &time);

    void setStatus(int status);
    int status()const;

signals:
    void requestSessionWindow();
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

    bool event(QEvent *event);

private slots:
    void hideCard();
private:
    Ui::SessionItem *ui;
    class SessionItemPrivate *p_d;
    friend class SessionItemPrivate;
};

#endif // SESSIONITEM_H
