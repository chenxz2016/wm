#include "messageview.h"

class MessageViewPrivate
{};

MessageView::MessageView(QWidget *parent)
    : QWidget(parent)
{

}

void MessageView::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void MessageView::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void MessageView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QWidget::mouseDoubleClickEvent(event);
}

void MessageView::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}

void MessageView::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void MessageView::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);
}

void MessageView::update()
{

}

QRect MessageView::itemRect(MessageViewItem *item)
{
    Q_UNUSED(item)
    return QRect();
}

MessageViewItem *MessageView::selectItem()
{
    return 0;
}
