#include "mainwindow.h"
#include "scrollbutton.h"
#include "ui_mainwindow.h"
#include "ui_talkitem.h"
#include "mainwindow_p.h"
#include "ui_switchorexit.h"

#include "show/wmshow.h"
#include "hide/wmhide.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QTreeWidget>
#include <QMenu>
#include <QBitmap>
#include <systemsetting.h>
#include <qssloader.h>
#include <QWidgetAction>
#include <talkmanage.h>

#include <skin/skinsetting.h>

#include <menu/menu.h>


static QPixmap pixmap_to_round(const QPixmap &src, qreal radius)
{
    if (src.isNull()) {
        return QPixmap();
    }

    QSizeF size(2*radius, 2*radius);
    QImage dst(size.toSize(),QImage::Format_ARGB32);
    QImage img(size.toSize(),QImage::Format_ARGB32);

    QPainter painter(&dst);
    painter.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(dst.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    QPainter ptr(&img);
    ptr.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    ptr.setCompositionMode(QPainter::CompositionMode_Source);
    ptr.fillRect(img.rect(), Qt::transparent);
    QPainterPath path;
    path.addEllipse(QRectF(0, 0, size.width(), size.height()));
    ptr.fillPath(path,Qt::white);
    ptr.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    ptr.end();
    painter.drawImage(dst.rect(),img);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawImage(dst.rect(),src.scaled(size.toSize()).toImage());

    return QPixmap::fromImage(dst);
}



MainWindow::MainWindow(WMTrayIcon *tray_icon,QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::MainWindow)
    ,p_d(new MainWindowPrivate(tray_icon,this))
{
    p_d->init();

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAutoFillBackground(false);
    setMouseTracking(true);

#if 1// WM_TEST
    sessionViewTest();

    /* Groups View Test. */
    QMap<QString,QVariant> map;
    map["type"] = GroupRootRole;
    map["select_enlarge"] = true;
    map["select_flag"] = false;

    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList("My Groups"));
    item->setIcon(0,QIcon(":/res/pds.png"));
    item->setData(0,ViewRole,GroupRole);
    item->setFlags(Qt::ItemIsEnabled);
    item->setData(0,ViewDataRole,map);
    p_d->group_view->addTopLevelItem(item);

    for(int i=0;i<5;i++)
    {
        QTreeWidgetItem *child = new QTreeWidgetItem(QStringList(QString("")));
        map["type"] = GroupItemRole;
        child->setData(0,ViewRole,GroupRole);
        child->setData(0,ViewDataRole,map);
        item->addChild(child);
        GroupItem *gitem = new GroupItem;
        p_d->group_view->setItemWidget(child,0,gitem);
        p_d->map[child] = gitem;
    }


    /* Multitalk View Test. */
    map["type"] = GroupRootRole;
    map["select_enlarge"] = true;
    map["select_flag"] = false;

    item = new QTreeWidgetItem(QStringList("MultipleTalk"));
    item->setIcon(0,QIcon(":/res/pds.png"));
    item->setData(0,ViewRole,GroupRole);
    item->setFlags(Qt::ItemIsEnabled);
    item->setData(0,ViewDataRole,map);
    p_d->multitalk_view->addTopLevelItem(item);

    for(int i=0;i<5;i++)
    {
        QTreeWidgetItem *child = new QTreeWidgetItem(QStringList(QString("")));
        map["type"] = GroupItemRole;
        child->setData(0,ViewRole,GroupRole);
        child->setData(0,ViewDataRole,map);
        item->addChild(child);
        MultiTalkItem *mitem = new MultiTalkItem;
        p_d->multitalk_view->setItemWidget(child,0,mitem);
    }

    /* Contact View Test. */
    map["type"] = ContactRootRole;
    map["select_enlarge"] = true;
    map["select_flag"] = false;

    item = new QTreeWidgetItem(QStringList("My Friends"));
    item->setIcon(0,QIcon(":/res/pds.png"));
    item->setData(0,ViewRole,ContactRole);
    item->setFlags(Qt::ItemIsEnabled);
    item->setData(0,ViewDataRole,map);
    p_d->contact_view->addTopLevelItem(item);

    for(int i=0;i<5;i++)
    {
        QTreeWidgetItem *child = new QTreeWidgetItem(QStringList(QString("")));
        map["type"] = ContactItemRole;
        child->setData(0,ViewRole,ContactRole);
        child->setData(0,ViewDataRole,map);
        item->addChild(child);
        ContactItem *citem = new ContactItem;
        p_d->contact_view->setItemWidget(child,0,citem);
    }
#endif

    ui->icon->setPixmap(pixmap_to_round(QPixmap(":/res/mainwindow/icon.jpg"),ui->icon->width()/2-2));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete p_d;
}

void MainWindow::sessionViewTest()
{
    for(int i=0;i<5;i++)
    {
        QListWidgetItem *item = new QListWidgetItem;
        p_d->session_view->addItem(item);
        SessionItem *si = new SessionItem(this);
        si->setObjectName(QString::number(i));
        p_d->session_view->setItemWidget(item,si);
    }

    QListWidgetItem *item = new QListWidgetItem;
    SessionItem *i = new SessionItem(this);
    i->setDescribeName("Verified Message");
    i->setLastMessage("XXX apply to join Groups.");
    i->setLastTime(QDateTime::currentDateTime());
    p_d->session_view->addItem(item);
    p_d->session_view->setItemWidget(item,i);

    item = new QListWidgetItem;
    i = new SessionItem(this);
    i->setDescribeName("Friend Photo");
    i->setLastMessage("XXX public say.");
    i->setLastTime(QDateTime::currentDateTime());
    p_d->session_view->addItem(item);
    p_d->session_view->setItemWidget(item,i);
}

void MainWindow::updateFriends(QVariant d)
{
    p_d->contact_view->appendContacts(d);
}

void MainWindow::updateGroups(QVariant d)
{
    p_d->group_view->appendGroups(d);
}

void MainWindow::updateSessions(QVariant d)
{
    Q_UNUSED(d)
}

void MainWindow::openSessionWindow(SessionItem *item)
{
    if(!item)
        return ;

    QString name = item->objectName();
    QWidget *w = TalkManage::instance()->find(name);
    if(!w)
    {
        w = new ContactTalk;
        w->setObjectName(name);
    }
    TalkManage::instance()->addTab(w);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==ui->icon)
        p_d->iconEvent(event);

    if(watched==p_d->short_intro)
        p_d->shortIntroEvent(event);

    if(watched==ui->weather)
        p_d->weatherEvent(event);

    if(watched==p_d->weather)
        p_d->weatherViewEvent(event);

    if(event->type()==QEvent::MouseMove)
    {
        QPointF p(mapFromGlobal(QCursor::pos()));
        QMouseEvent e(QEvent::MouseMove,p,\
                      Qt::NoButton,Qt::NoButton,Qt::NoModifier);
        p_d->mouseMoveEvent(&e);
    }
    return QWidget::eventFilter(watched,event);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    p_d->drawWindowEdge(&painter);
    p_d->drawBackground(&painter);
    QWidget::paintEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    p_d->mousePressEvent(event);
    QWidget::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    p_d->mouseMoveEvent(event);
    QWidget::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    p_d->mouseReleaseEvent(event);
    QWidget::mouseReleaseEvent(event);
}

void MainWindow::enterEvent(QEvent *event)
{
    p_d->enterEvent(event);
    QWidget::enterEvent(event);
}

void MainWindow::leaveEvent(QEvent *event)
{
    p_d->leaveEvent(event);
    QWidget::leaveEvent(event);
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    p_d->nativeEvent(eventType,message,result);
    return QWidget::nativeEvent(eventType,message,result);
}

void MainWindow::moveEvent(QMoveEvent *event)
{
//    int x = geometry().right();
//    int y = ui->weather->mapToGlobal(ui->weather->pos()).y();
//    ui->weather->move(QPoint(x,y));
    QWidget::moveEvent(event);
}


void MainWindow::on_level_clicked()
{
    qDebug() << "level pressed";
}



void MainWindow::on_groups_button_toggled(bool checked)
{
    if(checked)
        ui->groups_stacked->setCurrentWidget(ui->group);
}


void MainWindow::on_multitalk_button_toggled(bool checked)
{
    if(checked)
        ui->groups_stacked->setCurrentWidget(ui->multitalk);
}

void MainWindow::on_online_button_toggled(bool checked)
{
    if(checked)
        ui->groups_stacked->setCurrentWidget(ui->chatter);
}

void MainWindow::on_create_button_clicked()
{
    QList<QAction *> list;
    list.append(ui->createGroups);
    list.append(ui->createMultitalk);
    QPoint point(ui->create_button->x(),ui->create_button->y()+ui->create_button->height());
    QMenu::exec(list,ui->group_bar->mapToGlobal(point));
}

void MainWindow::on_close_clicked()
{
    close();
}

void MainWindow::on_min_clicked()
{
    hide();
}

void MainWindow::on_contact_toggle_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->contact);
}

void MainWindow::on_groups_toggle_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->groups);
}

void MainWindow::on_sessions_toggle_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->session);
}

MainWindowPrivate::MainWindowPrivate(WMTrayIcon *ti,MainWindow *parent)
    :WindowImpl(parent)
    ,p(parent)
    ,hideWidget(0)
    ,actionTime(500)
    ,tray_icon(ti)
{
    timer.setSingleShot(true);
    timer.setInterval(actionTime);
    connect(&timer,SIGNAL(timeout()),this,SLOT(timerOut()));
}

void MainWindowPrivate::init()
{
    p->ui->setupUi(p);
    p->ui->icon->installEventFilter(p);
    p->ui->weather->installEventFilter(p);

    user_card = new DetailsCard;
    user_card->installEventFilter(p);
    short_intro = new BriefCard;
    short_intro->installEventFilter(p);
    weather = new WeatherView;
    weather->installEventFilter(p);

    group_view = new GroupView;
    group_view->setMouseTracking(true);

    group_view->setIndentation(0);
    group_view->header()->setVisible(false);
    group_view->setObjectName("group_view");
    QssLoader::load(group_view,"mainwindow-group-view");
    p->ui->group->layout()->addWidget(group_view);

    multitalk_view = new GroupView;

    multitalk_view->setIndentation(0);
    multitalk_view->header()->setVisible(false);
    multitalk_view->setObjectName("multitalk_view");
    QssLoader::load(multitalk_view,"mainwindow-multitalk-view");
    p->ui->multitalk->layout()->addWidget(multitalk_view);

    contact_view = new ContactView;
    contact_view->setIndentation(0);
    contact_view->header()->setVisible(false);
    contact_view->setObjectName("contact_view");
    QssLoader::load(contact_view,"mainwindow-contact-view");
    p->ui->contact->layout()->addWidget(contact_view);

    session_view = new SessionView;
    session_view->setFocusPolicy(Qt::NoFocus);
    session_view->setObjectName("session_view");
    QssLoader::load(session_view,"mainwindow-session-view");
    p->ui->session->layout()->addWidget(session_view);

    main_menu = new QMenu;
    QssLoader::load(main_menu,"mainwindow-setting-menu");

    main_menu->addAction(p->ui->main_setting);
    main_menu->addAction(p->ui->mm);
    main_menu->addAction(p->ui->file_assitance);
    main_menu->addAction(p->ui->enshiren);
    main_menu->addSeparator();
    main_menu->addAction(p->ui->wmms);
    main_menu->addAction(p->ui->security);
    main_menu->addAction(p->ui->help);
    main_menu->addAction(p->ui->upgrade);

    QWidgetAction *action = new QWidgetAction(main_menu);
    SwitchOrExit *soe = new SwitchOrExit;
    action->setDefaultWidget(soe);
    main_menu->addAction(action);
}

void MainWindowPrivate::drawBackground(QPainter *painter)
{
    if(!p)
        return ;

    painter->save();
    painter->drawPixmap(borderWidth,borderWidth,p->width()-2*borderWidth,p->height()-2*borderWidth,QPixmap(":/res/mainwindow/m_bg.jpg"));
    painter->restore();
}

void MainWindowPrivate::iconEvent(QEvent *event)
{
    int x;
    int y;
    switch(event->type())
    {
    case QEvent::Enter:
        x = p->pos().x()-short_intro->width();
        y = p->ui->icon->mapToGlobal(p->ui->icon->pos()).y();
        WMAnimation::show_by_pos(short_intro,200,QPointF(x,y-20),QPointF(x,y));
        break;
    case QEvent::Leave:
        hideWidget = short_intro;
        timer.start();
        break;
    default:
        break;
    }
}

void MainWindowPrivate::userCardEvent(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::Enter:
        timer.stop();
        break;
    case QEvent::Leave:
        timer.start();
        break;
    default:
        break;
    }
}

void MainWindowPrivate::shortIntroEvent(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::Enter:
        timer.stop();
        break;
    case QEvent::Leave:
        timer.start();
        break;
    default:
        break;
    }
}

void MainWindowPrivate::weatherEvent(QEvent *event)
{
    if(!weather->animationEnable())
        return ;

    int x;
    int y;
    switch(event->type())
    {
    case QEvent::Enter:
        x = p->geometry().right();
        y = p->ui->weather->mapToGlobal(p->ui->weather->pos()).y();
        WMAnimation::show_by_pos(weather,200,QPointF(x,y-20),QPointF(x,y));
        break;
    case QEvent::Leave:
        hideWidget = weather;
        timer.start();
        break;
    default:
        break;
    }
}

void MainWindowPrivate::weatherViewEvent(QEvent *event)
{
    if(!weather->animationEnable())
        return ;

    switch(event->type())
    {
    case QEvent::Enter:
        timer.stop();
        break;
    case QEvent::Leave:
        timer.start();
        break;
    default:
        break;
    }
}


void MainWindowPrivate::timerOut()
{
    WMAnimation::hide_by_pos(hideWidget,80,\
                             hideWidget->pos(),
                             QPointF(hideWidget->x(),hideWidget->y()-30));
}


void MainWindow::on_skin_clicked()
{
    SkinSetting *setting = new SkinSetting;
    setting->show();
}

void MainWindow::on_menu_clicked()
{
    QPoint pos = ui->menu->mapToGlobal(ui->menu->rect().bottomLeft());
    p_d->main_menu->exec(pos);
}

void MainWindow::on_status_clicked()
{
    QMenu *menu = Menu::createMenu(ui->status);

    QssLoader::load(menu,"mainwindow-status-menu");

    menu->addAction(ui->online);
    menu->addAction(ui->mme);
    menu->addAction(ui->leave);
    menu->addAction(ui->bussy);
    menu->addAction(ui->dnd);
    menu->addAction(ui->hide);
    menu->addAction(ui->offline);
    menu->addSeparator();
    menu->addAction(ui->novoice);
    menu->addAction(ui->noblink);
    menu->addSeparator();
    menu->addAction(ui->lock);
    menu->addSeparator();
    menu->addAction(ui->setting);
    menu->addAction(ui->card);
    menu->addAction(ui->center);

    QPoint pos = ui->status->mapToGlobal(ui->status->rect().bottomLeft());
    menu->exec(pos);
    delete menu;
}

void MainWindow::on_chatter_toggle_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->chatter);
}

void MainWindow::on_main_setting_triggered()
{
    SystemSetting *setting = new SystemSetting;
    setting->show();
}

SwitchOrExit::SwitchOrExit(QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::SwitchOrExit)
{
    ui->setupUi(this);
    connect(ui->switcher,SIGNAL(clicked()),this,SIGNAL(switchAccount()));
    connect(ui->exit,SIGNAL(clicked()),this,SIGNAL(exitAccount()));
}



void MainWindow::on_bottom_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    menu.addAction(new QAction("test"));
    menu.exec(ui->bottom->mapToGlobal(pos));
}
