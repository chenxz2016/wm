#ifndef LOGINACCOUNTITEM_H
#define LOGINACCOUNTITEM_H

#include <QScrollArea>
#include <QWidget>

namespace Ui {
class LoginWindow;
class LoginAccountItem;
}

class LoginAccountItem;

class LoginAccountView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor hoverColor READ hoverColor WRITE setHoverColor)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(int hoverHeight READ hoverHeight WRITE setHoverHeight)
    Q_PROPERTY(int itemHeight READ itemHeight WRITE setItemHeight)
public:
    LoginAccountView(QWidget *parent = 0);
    ~LoginAccountView();

    void appendAccount(LoginAccountItem *item);
    void removeAccount(LoginAccountItem *item);
    void removeAccount(const QString &id);

    int hoverHeight()const;
    void setHoverHeight(int height);

    void setItemHeight(int height);
    int itemHeight()const;

    QColor hoverColor()const;
    void setHoverColor(const QColor &color);

    QColor color()const;
    void setColor(const QColor &color);

    void updateGeometry();
signals:
    void itemSelected(LoginAccountItem *item);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private slots:
    void removeItem(LoginAccountItem *item);
private:
    class LoginAccountViewPrivate *p_d;
};

class LoginAccountItem : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPixmap icon READ icon WRITE setIcon)
    Q_PROPERTY(QString accountName READ accountName WRITE setAccountName)
    Q_PROPERTY(QString accountID READ accountID WRITE setAccountID)
public:
    explicit LoginAccountItem(QWidget *parent = 0);
    ~LoginAccountItem();

    QPixmap icon()const;
    void setIcon(const QPixmap &pixmap);

    QString accountName()const;
    void setAccountName(const QString &name);

    QString accountID()const;
    void setAccountID(const QString id);

    QString accountPWD()const;
    void setAccountPWD(const QString &pwd);

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
signals:
    void deleteRequest(LoginAccountItem *);
protected:

private slots:
    void on_remove_clicked();

private:
    class LoginAccountItemPrivate *p_d;
    Ui::LoginAccountItem *ui;
    friend class LoginAccountView;
    friend class LoginAccountItemPrivate;
};

#endif // LOGINACCOUNTITEM_H
