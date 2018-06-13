#include "expressionwidget.h"
#include "ui_expressionwidget.h"
#include "ui_expressionhistory.h"
#include "contacttalk.h"

#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QTimer>
#include <QDebug>

static QPixmap selectExpression(QWidget *parent,const QPoint &pos)
{
    if(parent)
    {
        QWidget *w = parent->childAt(pos);
        if(w)
            return w->property("pixmap").value<QPixmap>();
    }
    return QPixmap();
}

class ExpressionWidgetPrivate
{
public:
    ExpressionWidgetPrivate()
//        :m_parentFoucsOut(false)
//        ,m_focuseParent(0)
//        ,m_enterFlag(false)
//        ,m_hideFlag(false)
    {
    }
//    bool m_parentFoucsOut;
//    TalkWidget *m_focuseParent;
//    bool m_enterFlag;
//    bool m_hideFlag;
};

ExpressionWidget::ExpressionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExpressionWidget)
{
    ui->setupUi(this);
    p_d = new ExpressionWidgetPrivate;

    setWindowFlags(Qt::Widget|Qt::FramelessWindowHint);
}

ExpressionWidget::~ExpressionWidget()
{
    delete ui;
    delete p_d;
}

void ExpressionWidget::animationShow(const QSize &start,const QSize &end,const QPoint &globalPos, Qt::Corner corner)
{
    QPoint pos;
    switch(corner)
    {
    case Qt::TopLeftCorner:
        pos = globalPos;
        break;
    case Qt::TopRightCorner:
        pos = globalPos;
        pos.setX(globalPos.x()-width());
        break;
    case Qt::BottomLeftCorner:
        pos = globalPos;
        pos.setY(globalPos.y()-height());
        break;
    case Qt::BottomRightCorner:
        pos.setX(globalPos.x()-width());
        pos.setY(globalPos.y()-height());
        break;
    }
    move(pos);
    hideAll();
    QWidget::show();

    QPropertyAnimation *animation= new QPropertyAnimation;
    animation->setTargetObject(this);
    animation->setPropertyName("geometry");
    QRect startr(QPoint(globalPos.x(),globalPos.y()-start.height()),start);
    QRect endr(QPoint(globalPos.x(),globalPos.y()-end.height()),end);
    animation->setStartValue(startr);
    animation->setEndValue(endr);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation,SIGNAL(finished()),this,SLOT(showAll()));
}

void ExpressionWidget::mousePressEvent(QMouseEvent *event)
{
    QPixmap pixmap = selectExpression(this,event->pos());
    if(!pixmap.isNull())
    {
        emit selectedExpression(pixmap.scaled(QSize(36,36),Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));
        emit aboutToHide();
        hide();
    }
    QWidget::mousePressEvent(event);
}

void ExpressionWidget::showEvent(QShowEvent *event)
{
    setFocus();
    QWidget::showEvent(event);
}

void ExpressionWidget::focusOutEvent(QFocusEvent *event)
{
    emit aboutToHide();
    hide();
    QWidget::focusOutEvent(event);
}

/*
void ExpressionWidget::enterEvent(QEvent *event)
{
    p_d->m_enterFlag = true;
    QWidget::enterEvent(event);
}

void ExpressionWidget::leaveEvent(QEvent *event)
{
    p_d->m_enterFlag = false;
    QWidget::leaveEvent(event);
}
*/

void ExpressionWidget::hideAll()
{
    ui->title->setVisible(false);
    ui->diy->setVisible(false);
    ui->setting->setVisible(false);
    ui->tabWidget->setVisible(false);
}

void ExpressionWidget::showAll()
{
    ui->title->setVisible(true);
    ui->diy->setVisible(true);
    ui->setting->setVisible(true);
    ui->tabWidget->setVisible(true);
    setFocus();
}


class ExpressionHistoryPrivate
{
public:
    ExpressionHistoryPrivate(Ui::ExpressionHistory *ui)
    {
        m_expressionList.append(ui->expression_1);
        m_expressionList.append(ui->expression_2);
        m_expressionList.append(ui->expression_3);
        m_expressionList.append(ui->expression_4);
        m_expressionList.append(ui->expression_4);
        m_expressionList.append(ui->expression_5);
        m_expressionList.append(ui->expression_6);
        m_expressionList.append(ui->expression_7);
        m_expressionList.append(ui->expression_8);
        m_expressionList.append(ui->expression_9);
        m_expressionList.append(ui->expression_10);
        m_expressionList.append(ui->expression_11);
        m_expressionList.append(ui->expression_12);
        m_expressionList.append(ui->expression_13);
        m_expressionList.append(ui->expression_14);
        m_expressionList.append(ui->expression_15);
    }

    QList<QPixmap> m_historyList;
    QList<QLabel *> m_expressionList;
    QTimer *timer;
};

ExpressionHistory::ExpressionHistory(QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::ExpressionHistory)
{
    ui->setupUi(this);
    p_d = new ExpressionHistoryPrivate(ui);
    p_d->timer = new QTimer(this);
    p_d->timer->setInterval(200);
    p_d->timer->setSingleShot(true);
    connect(p_d->timer,SIGNAL(timeout()),this,SLOT(hide()));

    setWindowFlags(Qt::Widget|Qt::FramelessWindowHint);
}

ExpressionHistory::~ExpressionHistory()
{
    delete ui;
    delete p_d;
}

void ExpressionHistory::show(const QPoint &globalPos, Qt::Corner corner)
{
    QPoint pos;
    switch(corner)
    {
    case Qt::TopLeftCorner:
        pos = globalPos;
        break;
    case Qt::TopRightCorner:
        pos = globalPos;
        pos.setX(globalPos.x()-width());
        break;
    case Qt::BottomLeftCorner:
        pos = globalPos;
        pos.setY(globalPos.y()-height());
        break;
    case Qt::BottomRightCorner:
        pos.setX(globalPos.x()-width());
        pos.setY(globalPos.y()-height());
        break;
    }
    move(pos);
    p_d->timer->stop();
    QWidget::show();
}

void ExpressionHistory::appendExpression(const QPixmap &pixmap)
{
    p_d->m_historyList.append(pixmap);
    sort();
}

void ExpressionHistory::animationHide()
{
    p_d->timer->start();
}

void ExpressionHistory::mousePressEvent(QMouseEvent *event)
{
    QPixmap pixmap = selectExpression(this,event->pos());
    if(!pixmap.isNull())
        emit selectedExpression(pixmap);
    QWidget::mousePressEvent(event);
}

void ExpressionHistory::leaveEvent(QEvent *event)
{
    animationHide();
    QWidget::leaveEvent(event);
}

void ExpressionHistory::sort()
{
    QList<QLabel *>::Iterator expressionIt = p_d->m_expressionList.begin();
    QList<QPixmap>::Iterator historyIt = p_d->m_historyList.begin();
    for(;expressionIt!=p_d->m_expressionList.end() && historyIt!=p_d->m_historyList.end();historyIt++,expressionIt++)
    {
        (*expressionIt)->setPixmap(*historyIt);
    }
}
