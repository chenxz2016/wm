#ifndef SESSIONVIEW_H
#define SESSIONVIEW_H

#include <QListWidget>

class SessionItem;

class SessionView : public QListWidget
{
    Q_OBJECT
public:
    SessionView(QWidget *parent = 0);
    ~SessionView();
public slots:
    void stick(bool);
    void cancelStick(bool);
    void removeItem(bool);
private slots:
    void popMenu(QPoint);

private:
    class SessionViewPrivate *p_d;
};

#endif // SESSIONVIEW_H
