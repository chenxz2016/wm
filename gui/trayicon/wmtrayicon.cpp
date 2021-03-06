#include "wmtrayicon.h"
#include "loginwindow.h"
#include "mainwindow.h"
#include "contacttalk.h"
#include "expressionwidget.h"
#include "photorecord.h"
#include "photoviewer.h"

#include <QApplication>
#include <QEvent>
#include <QIcon>
#include <QMenu>

#include <close/wmclose_p.h>
#include <close/wmclose.h>

#include <wmcore/wmcore.h>
#include <wm_protocol.h>
#include <wmp_user.h>
#include <wmp_group.h>


class WMTrayIconPrivate
{
public:
    WMTrayIconPrivate(WMTrayIcon *parent)
        :p(parent)
        ,login_window(0)
        ,main_window(0)
    {}

    void init()
    {
        p->setContextMenu(new QMenu);
        p->setIcon(QIcon(":/res/trayicon/wm_icon.png"));
        p->setToolTip(p->tr("Walking Message"));
        exit_action = new QAction(p->tr("Exit"));
        p->contextMenu()->addAction(exit_action);

        QObject::connect(p,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),p,SLOT(on_activatedSlot(QSystemTrayIcon::ActivationReason)));


        WMCore::globalInstance()->start();
        /* wait for exec. */
        QThread::msleep(10);
        WMCore::globalInstance()->registerService(p,"ClientService");
    }

    void initLoginWindow()
    {
        login_window = new LoginWindow(p);
        login_window->show();
    }

    void initMainWindow()
    {
        main_window = new MainWindow(p);
        main_window->show();
    }

    void closeLoginWindow()
    {
        login_window->deleteLater();
        login_window = 0;
    }

    void showLoginWindow()
    {
        if(login_window)
            login_window->setVisible(true);
    }

    void showMainWindow()
    {
        if(main_window)
            main_window->setVisible(true);
    }

    WMTrayIcon *p;
    LoginWindow *login_window;
    MainWindow *main_window;
    QAction *exit_action;

    QMap<int,QVariant> messageMap;
};

WMTrayIcon::WMTrayIcon(QObject *parent)
    :QSystemTrayIcon(parent)
    ,p_d(new WMTrayIconPrivate(this))
{
    p_d->init();
}

WMTrayIcon::~WMTrayIcon()
{
    delete p_d;
}

QVariant WMTrayIcon::serviceData()
{
    return QVariant();
}

void WMTrayIcon::setServiceData(QVariant data)
{
    QMap<QString,QVariant> map = data.toMap();
    if(map["service"].toString()!="ClientService")
        return ;

    int opt = map["opt"].toInt();
    switch(opt)
    {
    case WM::CSLoginID:
    {
        if(map["res"].toInt()!=WM::LoginSuccess)
            return ;

        /* login successfully */
        if(p_d->login_window)
        {
            /* change gui. */
            loginSuccess();

            /* fetch friends. */
            //fetchFriends();

            /* fetch groups. */
            fetchGroups();

            /* fetch sessions. */
            fetchSessions();
        }
        break;
    }
    case WM::CSUserID:
    {
        if(map["id"].toInt()==WMP_USER_FRIEND_ID)
            p_d->main_window->updateFriends(map);
        break;
    }
    case WM::CSGroupID:
    {
        if(map["id"].toInt()==WMP_GROUP_LIST_ID)
            p_d->main_window->updateGroups(map);
        break;
    }
    default:
        break;
    }
}

int WMTrayIcon::messageCount() const
{
    return p_d->messageMap.count();
}

void WMTrayIcon::init()
{
    p_d->initLoginWindow();
}

void WMTrayIcon::showNotice(int type, const QVariant &notice)
{
    p_d->messageMap[type] = notice;
    /* update message. */
}

void WMTrayIcon::loginSuccess()
{
    p_d->closeLoginWindow();
    p_d->initMainWindow();
}

void WMTrayIcon::fetchFriends()
{
    QMap<QString,QVariant> map;
    map["opt"] = WMP_PROTO_USER_ID;
    map["id"] = WMP_USER_FRIEND_ID;
    map["attr"] = 1;
    map["user_friend_attr"] = WMP_USER_FRIEND_LIST_REQ;
    WMCore::globalInstance()->flush("ClientService",map);
}

void WMTrayIcon::fetchGroups()
{
    QMap<QString,QVariant> map;
    map["opt"] = WMP_PROTO_GROUP_ID;
    map["attr"] = WMP_GROUP_LIST_REQ;
    map["id"] = WMP_GROUP_LIST_ID;
    WMCore::globalInstance()->flush("ClientService",map);
}

void WMTrayIcon::fetchSessions()
{
    QMap<QString,QVariant> map;
    map["opt"] = WMP_PROTO_SESSION_ID;
    map["attr"] = 1;
    WMCore::globalInstance()->flush("ClientService",map);
}

void WMTrayIcon::clearAction()
{
    contextMenu()->clear();
}

void WMTrayIcon::addAction(QAction *action)
{
    contextMenu()->removeAction(p_d->exit_action);
    contextMenu()->addAction(action);
    contextMenu()->addAction(p_d->exit_action);
}

void WMTrayIcon::addActions(const QList<QAction *> &actions)
{
    contextMenu()->removeAction(p_d->exit_action);
    contextMenu()->addActions(actions);
    contextMenu()->addAction(p_d->exit_action);
}

void WMTrayIcon::removeAction(QAction *action)
{
    contextMenu()->removeAction(action);
}

void WMTrayIcon::exit()
{
    if(p_d->login_window)
        p_d->login_window->deleteLater();

    if(p_d->main_window)
        p_d->main_window->deleteLater();

    qApp->quit();
}

void WMTrayIcon::on_activatedSlot(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case Trigger:
        p_d->showLoginWindow();
        p_d->showMainWindow();
        break;
    case DoubleClick:
        break;
    case MiddleClick:
        break;
    case Context:
        break;
    case Unknown:
        break;
    default:
        break;
    }
}
