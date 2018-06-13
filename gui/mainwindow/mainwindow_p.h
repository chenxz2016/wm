#ifndef MAINWINDOW_P_H
#define MAINWINDOW_P_H

#include "contactitem.h"
#include "contactview.h"
#include "groupitem.h"
#include "groupview.h"
#include "detailscard.h"
#include "briefcard.h"
#include "sessionitem.h"
#include "sessionview.h"
#include "contacttalk.h"
#include "viewdelegate.h"
#include "windowimpl.h"
#include "weatherview.h"

#include <QTimer>


namespace Ui
{
class SwitchOrExit;
}

class MainWindow;
class WMTrayIcon;


class SwitchOrExit : public QWidget
{
    Q_OBJECT
public:
    SwitchOrExit(QWidget *parent = 0);

signals:
    void switchAccount();
    void exitAccount();
private:
    Ui::SwitchOrExit *ui;
};

class MainWindowPrivate : public QObject, public WindowImpl
{
    Q_OBJECT
public:
    MainWindowPrivate(WMTrayIcon *ti,MainWindow *parent);

    void init();

    void drawBackground(QPainter *painter);

    void iconEvent(QEvent *event);

    void userCardEvent(QEvent *event);

    void shortIntroEvent(QEvent *event);

    void weatherEvent(QEvent *event);

    void weatherViewEvent(QEvent *event);

//    void nativeEvent(const QByteArray &eventType, void *message, long *result);

    MainWindow *p;
    DetailsCard *user_card;
    BriefCard *short_intro;
    QModelIndex index;
    QMap<QTreeWidgetItem*,GroupItem *> map;
    GroupView *group_view;
    GroupView *multitalk_view;
    ContactView *contact_view;
    SessionView *session_view;
    QWidget *hideWidget;
    QTimer timer;
    int actionTime;
    WeatherView *weather;
    QMenu *main_menu;
    WMTrayIcon *tray_icon;
protected slots:
    void timerOut();
};

#endif // MAINWINDOW_P_H
