#ifndef TALKMANAGE_H
#define TALKMANAGE_H

#include <QListWidget>
#include <QWidget>

namespace Ui {
class TalkManage;
class BubbleFontSelect;
}

class ExpressionHistory;
class ExpressionWidget;

class TextOptionSelect : public QListWidget
{
    Q_OBJECT
public:
    explicit TextOptionSelect(QWidget *parent = 0);
    void show();
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void focusOutEvent(QFocusEvent *event);
signals:
    void select(QString);
    void aboutToHide();
private slots:
    void clickedSlot(QListWidgetItem *item);
};

class BubbleFontSelect : public QWidget
{
    Q_OBJECT
public:
    BubbleFontSelect(QWidget *parent = 0);
    ~BubbleFontSelect();

signals:
    void selectFont(QFont);
private:
    Ui::BubbleFontSelect *ui;
};

class FontManage
{
public:
    virtual ~FontManage();

    static FontManage *manage();
    void setTarget(QWidget *talk);
    bool isCurrentTarget(QWidget *current);

    TextOptionSelect *customFont;
    TextOptionSelect *bubbleFontSize;

    TextOptionSelect *sysFont;
    TextOptionSelect *textFontSize;
protected:
    FontManage();
private:
    static FontManage *f_m;
    QWidget *target;
};


class ExpresssionManage
{
public:
    virtual ~ExpresssionManage();
    static ExpresssionManage *manage();
    void setTarget(QWidget *talk);
    bool isCurrentTarget(QWidget *current);
    ExpressionHistory *history;
    ExpressionWidget *expression;
protected:
    ExpresssionManage();
    static ExpresssionManage *e_m;
    QWidget *target;
};




class TalkManage : public QWidget
{
    Q_OBJECT
protected:
    explicit TalkManage(QWidget *parent = 0);
public:
    ~TalkManage();

    static TalkManage *instance();

    void addTab(QWidget *tab);

    void addTalk(QWidget *talk);
    void removeTalk(QWidget *talk);

    void mergeTab(QWidget *tab,const QPoint &oldPos);

    QList<QWidget *> talks()const;
    QWidget *find(const QString &name);

    void updateTalks();


    void setCurrentWidget(QWidget *widget);
    QWidget *currentWidget()const;
protected:
    void updateWidget();

    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    bool eventFilter(QObject *watched, QEvent *event);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    bool event(QEvent *event);
private slots:
    void currentTabChanged(int tab);
    void removeTab(int tab);

    void on_ctrl_toggled(bool checked);

    void on_tabbar_customContextMenuRequested(const QPoint &pos);

    void on_close_clicked();

private:
    static TalkManage *tm;

    Ui::TalkManage *ui;
    class TalkManagePrivate *p_d;
    friend class TalkManagePrivate;
    friend class ContactTalk;
};

#endif // TALKMANAGE_H
