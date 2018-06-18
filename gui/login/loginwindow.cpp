#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "ui_loginaccountitem.h"
#include "wmtrayicon.h"
#include "windowimpl.h"
#include "qrlogin.h"
#include "logosetting.h"
#include "networksetting.h"
#include "loginaccounts.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>
#include <QSequentialAnimationGroup>
#include <QStackedWidget>
#include <QSpinBox>
#include <QColorDialog>
#include <QMenu>
#include <QListWidget>
#include <QTimer>
#include <QMessageBox>
#include <QBitmap>

#include <close/wmclose_p.h>
#include <close/wmclose.h>

#include <polygon/polygonchange.h>

#include <QTextCodec>

#include <wmcore/wmcore.h>

#include <wm_protocol.h>

class LoginWindowPrivate : public WindowImpl
{
public:
    LoginWindowPrivate(WMTrayIcon *ti,LoginWindow *parent = 0)
        :WindowImpl(parent)
        ,topColor("#a43efe")
        ,bottomColor("#f1ffef")
        ,m_topTransparent(1.0)
        ,m_bottomTransparent(1.0)
        ,m_mouseChase(false)
        ,tray_icon(ti)
        ,p(parent)
    {
        w_p->setObjectName("LoginWindow");

        resizeFlag = false;
        qr_login = new QRLogin(parent);
        QObject::connect(qr_login,SIGNAL(goBack()),parent,SLOT(on_close_clicked()));
        if(parent)
            qr_login->move(0,-parent->height());
        qr_login->hide();

        logo_setting = new LogoSetting(parent);
        if(parent)
            logo_setting->move(0,parent->height());

        logo_setting->hide();
        QObject::connect(logo_setting,SIGNAL(cancel()),parent,SLOT(on_close_clicked()));

        network_setting = new NetworkSetting(parent);
        if(parent)
            network_setting->move(0,-parent->height());
        network_setting->hide();
        QObject::connect(network_setting,SIGNAL(cancel()),parent,SLOT(on_close_clicked()));
        QObject::connect(network_setting,SIGNAL(save()),parent,SLOT(saveNetworkSetting()));

        account_view = new LoginAccountView;
        QObject::connect(account_view,SIGNAL(itemSelected(LoginAccountItem*)),parent,SLOT(selectedAccount(LoginAccountItem*)));
        account_view->hide();
    }

    void drawBackground(QPainter *painter)
    {
        if(!w_p)
            return ;

        painter->save();
        painter->fillRect(QRect(borderWidth,w_p->height()/2,w_p->width()-2*borderWidth,w_p->height()/2-borderWidth),bottomColor);
        painter->restore();
    }

    void init()
    {
        p->ui->setupUi(p);

        p->ui->account->installEventFilter(p);
        p->ui->pwd->installEventFilter(p);

        QRegExp regx("[0-9]+$");
        QValidator *validator = new QRegExpValidator(regx, p->ui->account);
        p->ui->account->setValidator( validator );

#if 1 //WM_TEST
        for (int i = 0; i < 3; ++i)
        {
            LoginAccountItem* item = new LoginAccountItem(account_view);
            item->setAccountID(QString("121212%1").arg(i));
            item->setAccountName("Nihao");
            item->setIcon(QPixmap(":/res/login/icon.jpg"));
            item->setObjectName(QString("item:%1").arg(i));
            account_view->appendAccount(item);
        }
#endif

        p->setWindowFlags(Qt::SubWindow|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
        p->setAttribute(Qt::WA_TranslucentBackground);
        p->setMouseTracking(true);

        /* Set WMTrayIcon Action. */
        QAction *action = new QAction(p->tr("Main Control Panal"));
        QObject::connect(action,SIGNAL(triggered(bool)),p,SLOT(show()));
        tray_icon->addAction(action);
    }

    QRLogin *qr_login;
    LogoSetting *logo_setting;
    NetworkSetting *network_setting;
    LoginAccountView *account_view;
    QColor topColor;
    QColor bottomColor;
    float m_topTransparent;
    float m_bottomTransparent;
    bool m_mouseChase;
    QString m_chaseStyle;

    WMTrayIcon *tray_icon;
    LoginWindow *p;
};


LoginWindow::LoginWindow(WMTrayIcon *tray_icon,QWidget *parent)
    : QWidget(parent)
    ,ui(new Ui::LoginWindow)
    ,p_d(new LoginWindowPrivate(tray_icon,this))
{
    p_d->init();
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete p_d;
}

QColor LoginWindow::topBgColor() const
{
    return p_d->topColor;
}

void LoginWindow::setTopBgColor(const QColor &color)
{
    p_d->topColor = color;
    update();
}

QColor LoginWindow::bottomColor() const
{
    return p_d->bottomColor;
}

void LoginWindow::setBottomColor(const QColor &color)
{
    p_d->bottomColor = color;
    update();
}

float LoginWindow::topTransparent() const
{
    return p_d->m_topTransparent;
}

void LoginWindow::setTopTransparent(float transparent)
{
    if(transparent<0 || transparent >1.000000)
        return ;
    p_d->m_topTransparent = transparent;
    update();
}

float LoginWindow::bottomTransparent() const
{
    return p_d->m_bottomTransparent;
}

void LoginWindow::setBottomTransparent(float transparent)
{
    if(transparent<0 || transparent >1.000000)
        return ;
    p_d->m_bottomTransparent = transparent;
    update();
}

bool LoginWindow::mouseChase() const
{
    return p_d->m_mouseChase;
}

void LoginWindow::setMouseChase(bool chase)
{
    p_d->m_mouseChase = chase;
    update();
}

QString LoginWindow::chaseStyle() const
{
    return p_d->m_chaseStyle;
}

void LoginWindow::setChaseStyle(const QString &chase)
{
    p_d->m_chaseStyle = chase;
}

void LoginWindow::animationClose()
{
    WMAnimation::wm_close(this,WMAnimation::Single,300);
    p_d->tray_icon->setVisible(false);
}

void LoginWindow::startLogin()
{
    if(ui->account->text().isEmpty() || ui->pwd->text().isEmpty())
    {
        /* gives tips to user. */
    }

    /* start to login server. */
    QMap<QString,QVariant> map;
    map["opt"] = WMP_PROTO_LOGIN_KEY_ID;
    map["account"]  = ui->account->text().toInt();
    map["pwd"]  = ui->pwd->text();
    WMCore::globalInstance()->flush("ClientService",map);

    /* set ui logining. */
}

void LoginWindow::setSystemIcon(WMTrayIcon *tray_icon)
{
    p_d->tray_icon = tray_icon;
}

WMTrayIcon *LoginWindow::systemIcon() const
{
    return p_d->tray_icon;
}

void LoginWindow::mouseMoveEvent(QMouseEvent *event)
{
    p_d->mouseMoveEvent(event);
    QWidget::mouseMoveEvent(event);
}

void LoginWindow::mousePressEvent(QMouseEvent *event)
{
    {
        ui->switcher->setChecked(false);
        p_d->account_view->setHidden(true);
    }
    p_d->mousePressEvent(event);
    QWidget::mousePressEvent(event);
}

void LoginWindow::mouseReleaseEvent(QMouseEvent *event)
{
    p_d->mouseReleaseEvent(event);
    QWidget::mouseReleaseEvent(event);
}

void LoginWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    p_d->drawWindowEdge(&painter);
    p_d->drawBackground(&painter);
    QWidget::paintEvent(event);
}

void LoginWindow::closeEvent(QCloseEvent *event)
{
    p_d->account_view->close();
    QWidget::closeEvent(event);
}

void LoginWindow::resizeEvent(QResizeEvent *event)
{
    p_d->qr_login->resize(width()-2*p_d->borderWidth,height()-2*p_d->borderWidth-28);
    p_d->logo_setting->resize(width()-2*p_d->borderWidth,height()-2*p_d->borderWidth-ui->quickWidget->height());
    p_d->network_setting->resize(width()-2*p_d->borderWidth,height()-2*p_d->borderWidth-28);
    QWidget::resizeEvent(event);
}

bool LoginWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(ui->account==watched && event->type() == QEvent::FocusIn)
    {
        if(ui->account->text().isEmpty())
            ui->account->setPlaceholderText("");

        QTimer::singleShot(0,ui->account,SLOT(selectAll()));
        return false;
    }
    if(ui->account==watched && event->type() == QEvent::FocusOut)
    {
        if(ui->account->text().isEmpty())
            ui->account->setPlaceholderText("WMID/Telephone/EMail");
        return false;
    }
    if(ui->pwd==watched && event->type() == QEvent::FocusIn)
    {
        if(ui->pwd->text().isEmpty())
            ui->pwd->setPlaceholderText("");

        return false;
    }
    if(ui->pwd==watched && event->type() == QEvent::FocusOut)
    {
        if(ui->pwd->text().isEmpty())
            ui->pwd->setPlaceholderText("Password");

        return false;
    }
    return QWidget::eventFilter(watched,event);
}

void LoginWindow::recvData(QVariant data)
{
    QMap<QString,QVariant> map = data.toMap();
    int res = map["login_result"].toInt();
    switch(res)
    {
    case WM::LoginSuccess:
        p_d->tray_icon->loginSuccess();
        QWidget::close();
        deleteLater();
        break;
    case WM::PWDError:
        QMessageBox::information(this,"Login Failed","Reason:"+map["reason"].toString());
        break;
    case WM::Timeout:
        QMessageBox::information(this,"Login Failed","Reason: Login timeout.");
        break;
    case WM::WaitForVerify:

        break;
    default:
        break;
    }
}

void LoginWindow::selectedAccount(LoginAccountItem *item)
{
    {
        ui->switcher->setChecked(false);
        p_d->account_view->setHidden(true);
    }
    ui->account->setText(item->accountID());
    ui->pwd->setText(item->accountPWD());
}

void LoginWindow::saveNetworkSetting()
{
    on_close_clicked();

    // save network setting
}


void LoginWindow::on_visible_toggled(bool checked)
{
    if(checked)
    {
        ui->pwd->setEchoMode(QLineEdit::Password);
    }
    else
    {
        ui->pwd->setEchoMode(QLineEdit::Normal);
    }
}

void LoginWindow::on_close_clicked()
{
    if(p_d->qr_login->isVisible())
    {
        QPropertyAnimation *an1 = new QPropertyAnimation(p_d->qr_login, "pos");
        connect(an1,SIGNAL(finished()),p_d->qr_login,SLOT(hide()));
        an1->setEasingCurve(QEasingCurve::InQuad);
        an1->setDuration(1000);
        an1->setLoopCount(1);
        an1->setStartValue(QPoint(p_d->borderWidth,p_d->borderWidth+28));
        an1->setEndValue(QPoint(p_d->borderWidth,-height()));
        an1->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else if(p_d->logo_setting->isVisible())
    {
        QPropertyAnimation *an1 = new QPropertyAnimation(p_d->logo_setting, "pos");
        connect(an1,SIGNAL(finished()),p_d->logo_setting,SLOT(hide()));
        an1->setEasingCurve(QEasingCurve::InQuad);
        an1->setDuration(1000);
        an1->setLoopCount(1);
        an1->setStartValue(ui->quickWidget->geometry().bottomLeft());
        an1->setEndValue(QPoint(p_d->borderWidth,height()));
        an1->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else if(p_d->network_setting->isVisible())
    {
        QPropertyAnimation *an1 = new QPropertyAnimation(p_d->network_setting, "pos");
        connect(an1,SIGNAL(finished()),p_d->network_setting,SLOT(hide()));
        an1->setEasingCurve(QEasingCurve::InQuad);
        an1->setDuration(500);
        an1->setLoopCount(1);
        an1->setStartValue(QPoint(p_d->borderWidth,p_d->borderWidth+28));
        an1->setEndValue(QPoint(p_d->borderWidth,-height()));
        an1->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else
    {
        p_d->tray_icon->exit();
    }
}

void LoginWindow::on_min_clicked()
{
    hide();
}

void LoginWindow::on_qrcode_clicked()
{
    p_d->qr_login->raise();
    p_d->qr_login->show();
    ui->close->raise();
    ui->min->raise();

    QPropertyAnimation *an1 = new QPropertyAnimation(p_d->qr_login, "pos");
    an1->setEasingCurve(QEasingCurve::InQuad);
    an1->setDuration(1000);
    an1->setLoopCount(1);
    an1->setStartValue(QPoint(p_d->borderWidth,-height()));
    an1->setEndValue(QPoint(p_d->borderWidth,p_d->borderWidth+28));

    QPropertyAnimation *an = new QPropertyAnimation(p_d->qr_login, "pos");
    an->setEasingCurve(QEasingCurve::OutBounce);
    an->setDuration(1500);
    an->setLoopCount(1);
    an->setStartValue(QPoint(p_d->borderWidth,-50));
    an->setEndValue(QPoint(p_d->borderWidth,p_d->borderWidth+28));

    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
    group->addAnimation(an1);
    group->addAnimation(an);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void LoginWindow::on_logo_setting_clicked()
{
    p_d->logo_setting->raise();
    p_d->logo_setting->show();
    ui->close->raise();
    ui->min->raise();

    QPropertyAnimation *an = new QPropertyAnimation(p_d->logo_setting, "pos");
    an->setEasingCurve(QEasingCurve::OutQuad);
    an->setDuration(500);
    an->setLoopCount(1);
    an->setStartValue(QPoint(p_d->borderWidth,height()));
    an->setEndValue(ui->quickWidget->geometry().bottomLeft());
    an->start(QAbstractAnimation::DeleteWhenStopped);
}

void LoginWindow::on_account_returnPressed()
{
    startLogin();
}

void LoginWindow::on_pwd_returnPressed()
{
    startLogin();
}

void LoginWindow::on_login_clicked()
{
    startLogin();
}

void LoginWindow::on_switcher_toggled(bool checked)
{
    if(checked)
    {
        p_d->account_view->raise();
        int x = ui->account->x();
        int y = ui->account->y();
        int h = ui->account->height();
        int w = ui->account->width();
        QPoint p = mapToGlobal(QPoint(x,y+h));
        p_d->account_view->resize(w,115);
        p_d->account_view->move(p);
    }
    p_d->account_view->setHidden(!checked);
}

void LoginWindow::on_status_clicked()
{
    QMenu menu;
    menu.addAction(ui->online);
    menu.addAction(ui->mme);
    menu.addSeparator();
    menu.addAction(ui->leave);
    menu.addAction(ui->bussy);
    menu.addAction(ui->dndst);
    menu.addSeparator();
    menu.addAction(ui->hide);

    QPoint p = ui->status->mapToGlobal(ui->status->rect().bottomLeft());
    QAction *action = menu.exec(p);
    if(action)
    {
        ui->status->setIcon(action->icon());
    }
}

void LoginWindow::on_network_setting_clicked()
{
    p_d->network_setting->raise();
    p_d->network_setting->show();
    ui->close->raise();
    ui->min->raise();

    QPropertyAnimation *an1 = new QPropertyAnimation(p_d->network_setting, "pos");
    an1->setEasingCurve(QEasingCurve::InQuad);
    an1->setDuration(1000);
    an1->setLoopCount(1);
    an1->setStartValue(QPoint(p_d->borderWidth,-height()));
    an1->setEndValue(QPoint(p_d->borderWidth,p_d->borderWidth+28));

    QPropertyAnimation *an = new QPropertyAnimation(p_d->network_setting, "pos");
    an->setEasingCurve(QEasingCurve::OutBounce);
    an->setDuration(1500);
    an->setLoopCount(1);
    an->setStartValue(QPoint(p_d->borderWidth,-50));
    an->setEndValue(QPoint(p_d->borderWidth,p_d->borderWidth+28));

    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
    group->addAnimation(an1);
    group->addAnimation(an);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void LoginWindow::on_account_textEdited(const QString &arg1)
{
    if(arg1.isEmpty() || ui->pwd->text().isEmpty())
        ui->login->setEnabled(false);
    else
        ui->login->setEnabled(true);
}

void LoginWindow::on_pwd_textEdited(const QString &arg1)
{
    if(arg1.isEmpty() || ui->account->text().isEmpty())
        ui->login->setEnabled(false);
    else
        ui->login->setEnabled(true);
}
