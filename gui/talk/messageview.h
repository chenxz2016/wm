#ifndef MESSAGEVIEW_H
#define MESSAGEVIEW_H

#include <QWidget>

class MessageViewItem;

class MessageView : public QWidget
{
    Q_OBJECT
public:
    explicit MessageView(QWidget *parent = 0);

    void resizeWidth(int width);
    void resizeHeight(int height);
signals:

public slots:
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void update();

    QRect itemRect(MessageViewItem *item);

    MessageViewItem *selectItem();
private:
    class MessageViewPrivate *p_d;
};

#endif // MESSAGEVIEW_H
