#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QListView>
#include <QListWidget>
#include <QItemDelegate>

namespace Ui {
class LoginWindow;
}

class QVaraint;
class LoginAccountItem;
class WMTrayIcon;

class LoginWindow : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor topBgColor READ topBgColor WRITE setTopBgColor)
    Q_PROPERTY(QColor bottomColor READ bottomColor WRITE setBottomColor)
    Q_PROPERTY(float topTransparent READ topTransparent WRITE setTopTransparent)
    Q_PROPERTY(float bottomTransparent READ bottomTransparent WRITE setBottomTransparent)
    Q_PROPERTY(bool mouseChase READ mouseChase WRITE setMouseChase)
    Q_PROPERTY(QString chaseStyle READ chaseStyle WRITE setChaseStyle)
public:
    explicit LoginWindow(WMTrayIcon *tray_icon,QWidget *parent = 0);
    ~LoginWindow();

    QColor topBgColor()const;
    void setTopBgColor(const QColor &color);

    QColor bottomColor()const;
    void setBottomColor(const QColor &color);

    float topTransparent()const;
    void setTopTransparent(float transparent);

    float bottomTransparent()const;
    void setBottomTransparent(float transparent);

    bool mouseChase()const;
    void setMouseChase(bool chase);

    QString chaseStyle()const;
    void setChaseStyle(const QString &chase);

    void startLogin();

    void setSystemIcon(WMTrayIcon *tray_icon);
    WMTrayIcon *systemIcon()const;
public slots:
    void animationClose();
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
public slots:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void recvData(QVariant);

    void selectedAccount(LoginAccountItem *item);

    void saveNetworkSetting();

    void on_visible_toggled(bool checked);

    void on_close_clicked();

    void on_min_clicked();

    void on_qrcode_clicked();

    void on_account_returnPressed();

    void on_pwd_returnPressed();

    void on_login_clicked();

    void on_switcher_toggled(bool checked);

    void on_status_clicked();

    void on_logo_setting_clicked();

    void on_network_setting_clicked();

    void on_account_textEdited(const QString &arg1);

    void on_pwd_textEdited(const QString &arg1);

private:
    Ui::LoginWindow *ui;
    class LoginWindowPrivate *p_d;
    friend class LoginWindowPrivate;
};

#endif // LOGINWINDOW_H
