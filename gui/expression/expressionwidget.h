#ifndef EXPRESSIONWIDGET_H
#define EXPRESSIONWIDGET_H

#include <QWidget>

namespace Ui {
class ExpressionWidget;
class ExpressionHistory;
}

class ExpressionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExpressionWidget(QWidget *parent = 0);
    ~ExpressionWidget();

    void animationShow(const QSize &start,const QSize &end,const QPoint &globalPos,Qt::Corner corner=Qt::BottomLeftCorner);
signals:
    void selectedExpression(QPixmap);
    void aboutToHide();
protected:
    void mousePressEvent(QMouseEvent *event);
    void showEvent(QShowEvent *event);
//    void hideEvent(QHideEvent *event);
    void focusOutEvent(QFocusEvent *event);
private slots:
    void showAll();
private:
    void hideAll();
private:
    class ExpressionWidgetPrivate *p_d;
    Ui::ExpressionWidget *ui;
};

class ExpressionHistory : public QWidget
{
    Q_OBJECT
public:
    explicit ExpressionHistory(QWidget *parent = 0);
    ~ExpressionHistory();

    void show(const QPoint &globalPos,Qt::Corner corner=Qt::BottomLeftCorner);

    void appendExpression(const QPixmap &pixmap);
    void animationHide();
signals:
    void selectedExpression(QPixmap);
protected:
    void mousePressEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);
    void sort();
private:
    class ExpressionHistoryPrivate *p_d;
    Ui::ExpressionHistory *ui;
};

#endif // EXPRESSIONWIDGET_H
