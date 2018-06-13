#ifndef WMTRAYICON_H
#define WMTRAYICON_H

#include<QSystemTrayIcon>
#include <QVariant>

class LoginWindow;
class QAction;

class WMTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
    Q_PROPERTY(int messageCount READ messageCount)
    Q_PROPERTY(QVariant serviceData READ serviceData WRITE setServiceData)
public:
    explicit WMTrayIcon(QObject *parent = 0);
    ~WMTrayIcon();

    QVariant serviceData();
    void setServiceData(QVariant data);

    int messageCount()const;

    void init();
    void showNotice(int type,const QVariant &notice);
    void loginSuccess();

    void clearAction();
    void addAction(QAction *action);
    void addActions(const QList<QAction *> &actions);
    void removeAction(QAction *action);
    void exit();
private slots:
    void on_activatedSlot(QSystemTrayIcon::ActivationReason reason);
private:
    class WMTrayIconPrivate *p_d;
    friend class WMTrayIconPrivate;
};

#endif // WMTRAYICON_H
