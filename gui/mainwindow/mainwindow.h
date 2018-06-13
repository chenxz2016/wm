#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDateTime>
#include <QModelIndex>
#include <QWidget>

namespace Ui {
class MainWindow;
}


class PersonCard;
class ShortIntroduction;
class QTreeWidgetItem;
class GroupItem;
class GroupView;
class ContactView;
class AbstractItem;
class SessionView;
class SessionItem;
class WMTrayIcon;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(WMTrayIcon *tray_icon,QWidget *parent = 0);
    ~MainWindow();

#if 1 //WM_TEST
    void sessionViewTest();
#endif
public slots:
    void openSessionWindow(SessionItem *item);
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void moveEvent(QMoveEvent *event);
private slots:

    void on_level_clicked();

    void on_groups_button_toggled(bool checked);

    void on_multitalk_button_toggled(bool checked);

    void on_online_button_toggled(bool checked);

    void on_create_button_clicked();

    void on_close_clicked();

    void on_min_clicked();

    void on_contact_toggle_clicked();

    void on_groups_toggle_clicked();

    void on_sessions_toggle_clicked();

    void on_skin_clicked();

    void on_menu_clicked();

    void on_status_clicked();

    void on_chatter_toggle_clicked();

    void on_main_setting_triggered();

    void on_bottom_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    class MainWindowPrivate *p_d;
    friend class MainWindowPrivate;
};

#endif // MAINWINDOW_H
