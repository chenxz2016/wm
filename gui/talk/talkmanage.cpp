#include "talkmanage.h"
#include "ui_talkmanage.h"

#include <QDebug>
#include <QDrag>
#include <QFontDatabase>
#include <QLabel>
#include <QMenu>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>
#include <QTabBar>
#include <expressionwidget.h>
#include <qssloader.h>
#include <windowimpl.h>

ExpresssionManage *ExpresssionManage::e_m = 0;

FontManage *FontManage::f_m = 0;


TextOptionSelect::TextOptionSelect(QWidget *parent)
    :QListWidget(parent)
{
    connect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(clickedSlot(QListWidgetItem*)));
    setWindowFlags(Qt::Widget|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
}

void TextOptionSelect::show()
{
    setFocus();
    QWidget::show();
}

void TextOptionSelect::mouseMoveEvent(QMouseEvent *e)
{
    QListWidget::mouseMoveEvent(e);
}

void TextOptionSelect::focusOutEvent(QFocusEvent *event)
{
    emit aboutToHide();
    hide();
    QWidget::focusOutEvent(event);
}

void TextOptionSelect::clickedSlot(QListWidgetItem *item)
{
    if(item)
    {
        emit select(item->text());
        hide();
    }
}

BubbleFontSelect::BubbleFontSelect(QWidget *parent)
    :QWidget(parent)
{

}

BubbleFontSelect::~BubbleFontSelect()
{

}


FontManage::~FontManage()
{
    delete customFont;
    delete bubbleFontSize;
    delete sysFont;
    delete textFontSize;
}

FontManage *FontManage::manage()
{
    if(!f_m)
        f_m = new FontManage;
    return f_m;
}

void FontManage::setTarget(QWidget *talk)
{
    if(target==talk)
        return ;

    if(target)
    {
        QObject::disconnect(customFont,SIGNAL(select(QString)),target,SLOT(setFont(QString)));
        QObject::disconnect(customFont,SIGNAL(aboutToHide()),target,SLOT(customFontReset()));
        QObject::disconnect(bubbleFontSize,SIGNAL(select(QString)),target,SLOT(setFontSize(QString)));
        QObject::disconnect(bubbleFontSize,SIGNAL(aboutToHide()),target,SLOT(bubbleFontSizeReset()));
        QObject::disconnect(sysFont,SIGNAL(select(QString)),target,SLOT(setFont(QString)));
        QObject::disconnect(sysFont,SIGNAL(aboutToHide()),target,SLOT(sysFontReset()));
        QObject::disconnect(textFontSize,SIGNAL(select(QString)),target,SLOT(setFontSize(QString)));
        QObject::disconnect(textFontSize,SIGNAL(aboutToHide()),target,SLOT(textFontSizeReset()));
    }

    customFont->hide();
    bubbleFontSize->hide();
    sysFont->hide();
    textFontSize->hide();

    target = talk;
    QObject::connect(customFont,SIGNAL(select(QString)),target,SLOT(setFont(QString)));
    QObject::connect(customFont,SIGNAL(aboutToHide()),target,SLOT(customFontReset()));
    QObject::connect(bubbleFontSize,SIGNAL(select(QString)),target,SLOT(setFontSize(QString)));
    QObject::connect(bubbleFontSize,SIGNAL(aboutToHide()),target,SLOT(bubbleFontSizeReset()));
    QObject::connect(sysFont,SIGNAL(select(QString)),target,SLOT(setFont(QString)));
    QObject::connect(sysFont,SIGNAL(aboutToHide()),target,SLOT(sysFontReset()));
    QObject::connect(textFontSize,SIGNAL(select(QString)),target,SLOT(setFontSize(QString)));
    QObject::connect(textFontSize,SIGNAL(aboutToHide()),target,SLOT(textFontSizeReset()));
}

bool FontManage::isCurrentTarget(QWidget *current)
{
    return (target == current);
}

FontManage::FontManage()
    :target(0)
{
    customFont = new TextOptionSelect;
    QFontDatabase base;
    customFont->addItems(base.families());

    sysFont = new TextOptionSelect;
    sysFont->addItems(base.families());

    bubbleFontSize = new TextOptionSelect;
    for(int i=9;i<14;i++)
        bubbleFontSize->addItem(QString::number(i));

    textFontSize = new TextOptionSelect;
    for(int i=9;i<22;i++)
        textFontSize->addItem(QString::number(i));
}

ExpresssionManage::~ExpresssionManage()
{
    delete history;
    delete expression;
}

ExpresssionManage *ExpresssionManage::manage()
{
    if(!e_m)
        e_m = new ExpresssionManage;

    return e_m;
}

void ExpresssionManage::setTarget(QWidget *talk)
{
    if(target==talk)
        return ;

    if(target)
    {
        QObject::disconnect(expression,SIGNAL(selectedExpression(QPixmap)),target,SLOT(insertPixmap(QPixmap)));
        QObject::disconnect(expression,SIGNAL(aboutToHide()),target,SLOT(expressionReset()));
    }
    expression->hide();
    history->hide();

    target = talk;
    QObject::connect(expression,SIGNAL(selectedExpression(QPixmap)),talk,SLOT(insertPixmap(QPixmap)));
    QObject::connect(expression,SIGNAL(aboutToHide()),talk,SLOT(expressionReset()));
}

bool ExpresssionManage::isCurrentTarget(QWidget *current)
{
    return (target == current);
}

ExpresssionManage::ExpresssionManage()
    :target(0)
{
    history = new ExpressionHistory;
    expression = new ExpressionWidget;
}


static QPixmap combine_tab_and_talk_pixmap(const QPixmap &tab,const QPixmap &talk)
{
    int width = tab.width();
    if(width<talk.width())
        width = talk.width();

    QImage image(width,tab.height()+talk.height(),QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    QRect r((width-tab.width())/2,0,tab.width(),tab.height());
    painter.drawPixmap(r,tab);
    painter.drawPixmap(0,tab.height(),talk);
    return QPixmap::fromImage(image);
}

class MousePicture
{
public:
    MousePicture()
    {
        mp = new QLabel;
        mp->setWindowFlags(Qt::FramelessWindowHint);
        mp->setAttribute(Qt::WA_TranslucentBackground);
    }
    ~MousePicture()
    {
        delete mp;
    }

    void setPixmap(const QPixmap &pixmap)
    {
        mp->setPixmap(pixmap);
    }

    void move(const QPoint &pos)
    {
        mp->move(pos);
    }
    void setVisible(bool visible)
    {
        mp->setVisible(visible);
    }
private:
    QLabel *mp;
};

class TalkManagePrivate : public WindowImpl
{
public:
    TalkManagePrivate(TalkManage *parent)
        :WindowImpl(parent)
        ,p(parent)
        ,currentWidget(0)
        ,readySeperate(false)
    {}

    void init()
    {
        p->ui->setupUi(p);
        p->ui->input->installEventFilter(p);
        p->ui->tabbar->installEventFilter(p);
        p->ui->tabbar->setMouseTracking(true);

        p->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
        p->setAttribute(Qt::WA_TranslucentBackground);
        p->setAttribute(Qt::WA_Mapped);
        p->setMouseTracking(true);

        p->ui->tabbar->setTabsClosable(true);

        QObject::connect(p->ui->tabbar,SIGNAL(currentChanged(int)),p,SLOT(currentTabChanged(int)));
        QObject::connect(p->ui->tabbar,SIGNAL(tabCloseRequested(int)),p,SLOT(removeTab(int)));
    }

    bool tabbarEvent(QEvent *event)
    {
        QMouseEvent *me;
        static bool mouseFlag = false;
        int tab;
        switch(event->type())
        {
        case QEvent::MouseButtonPress:
            tab = p->ui->tabbar->tabAt(p->ui->tabbar->mapFromGlobal(QCursor::pos()));
            if(tab<0)
                break;

            mouseFlag = true;
            break;
        case QEvent::MouseMove:
            me = static_cast<QMouseEvent *>(event);
            if(!me)
                break;

            if(mouseFlag)
            {
                me->ignore();
                QRect r = p->ui->tabbar->tabRect(p->ui->tabbar->currentIndex());
                QPoint pos = p->ui->tabbar->mapFromGlobal(QCursor::pos());
                if(r.contains(pos))
                {
                    readySeperate = false;
                    p->ui->tabbar->setCursor(QCursor());
                    mp.setVisible(false);
                    QssLoader::load(p->ui->tabbar,"talkmanage-tabbar-dragin");
                }
                else
                {
                    readySeperate = true;
                    QPixmap tabPixmap = p->ui->tabbar->grab(r);
                    QPixmap talkPixmap = p->ui->stackedWidget->currentWidget()->grab();
                    mp.setVisible(true);
                    mp.setPixmap(combine_tab_and_talk_pixmap(tabPixmap,talkPixmap));
                    mp.move(QCursor::pos());
                    QssLoader::load(p->ui->tabbar,"talkmanage-tabbar-dragout");
                }
                return true;
            }
            break;
        case QEvent::MouseButtonRelease:
            mouseFlag = false;
            mp.setVisible(false);
            p->ui->tabbar->setCursor(QCursor());
            QssLoader::load(p->ui->tabbar,"talkmanage-tabbar-dragout");
            tab = p->ui->tabbar->currentIndex();
            if(tab<0 || !readySeperate)
                break;

            for(int i=0;i<p->ui->stackedWidget->count();i++)
            {
                QString name = p->ui->tabbar->tabData(tab).toString();
                QWidget *widget = p->ui->stackedWidget->widget(i);
                if(name==widget->objectName())
                {
                    p->ui->stackedWidget->removeWidget(widget);
                    widget->setParent(0);
                    p->ui->tabbar->removeTab(tab);
                    currentWidget = widget;
                    currentWidget->move(QCursor::pos());
                    currentWidget->show();
                    if(p->ui->stackedWidget->count()==1)
                    {
                        widget = p->ui->stackedWidget->widget(0);
                        p->ui->stackedWidget->removeWidget(widget);
                        widget->setParent(0);
                        widget->move(p->pos());
                        p->setVisible(false);
                        widget->show();
                    }
                    break;
                }
            }
            readySeperate = false;
            break;
        default:
            break;
        }
        return false;
    }

    void inputEvent(QEvent *event)
    {
        Q_UNUSED(event)
    }

    TalkManage *p;
    QList<QWidget *> talks;
    QWidget *currentWidget;
    MousePicture mp;
    bool readySeperate;
};

TalkManage *TalkManage::tm = 0;

TalkManage::TalkManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TalkManage),
    p_d(new TalkManagePrivate(this))
{
    p_d->init();
}

TalkManage::~TalkManage()
{
    delete ui;
    delete p_d;
}

TalkManage *TalkManage::instance()
{
    if(!tm)
        tm = new TalkManage;
    return tm;
}

void TalkManage::addTab(QWidget *tab)
{
    if(!p_d->talks.contains(tab))
        p_d->talks.append(tab);

    if(tab==p_d->currentWidget)
        return ;

    int index = ui->stackedWidget->indexOf(tab);
    if(index<0)
    {
        if(p_d->talks.count()>=2)
        {
            if(ui->stackedWidget->count()==0)
            {
                index = ui->stackedWidget->addWidget(p_d->currentWidget);
                ui->stackedWidget->setCurrentIndex(index);
                if(ui->tabbar->count()==1)
                {
                    ui->tabbar->setTabText(0,p_d->currentWidget->objectName());
                    ui->tabbar->setTabData(0,p_d->currentWidget->objectName());
                }
                else
                {
                    index = ui->tabbar->addTab(p_d->currentWidget->objectName());
                    ui->tabbar->setCurrentIndex(index);
                    ui->tabbar->setTabData(index,p_d->currentWidget->objectName());
                }

                if(tab!=p_d->currentWidget)
                {
                    index = ui->stackedWidget->addWidget(tab);
                    ui->stackedWidget->setCurrentIndex(index);
                    index = ui->tabbar->addTab(tab->objectName());
                    ui->tabbar->setCurrentIndex(index);
                    ui->tabbar->setTabData(index,tab->objectName());
                }
            }
            else
            {
                index = ui->stackedWidget->addWidget(tab);
                ui->stackedWidget->setCurrentIndex(index);
                index = ui->tabbar->addTab(tab->objectName());
                ui->tabbar->setCurrentIndex(index);
                ui->tabbar->setTabData(index,tab->objectName());
            }
            setVisible(true);
        }
        else
        {
            tab->show();
            p_d->currentWidget = tab;
            setVisible(false);
        }
    }
    else
    {
        for(int i=0;i<ui->tabbar->count();i++)
        {
            if(ui->tabbar->tabData(i).toString()==tab->objectName())
            {
                ui->tabbar->setCurrentIndex(i);
                break;
            }
        }
        ui->stackedWidget->setCurrentWidget(tab);
    }
}

void TalkManage::addTalk(QWidget *talk)
{
    if(p_d->talks.contains(talk))
        return ;

    p_d->talks.append(talk);
}

void TalkManage::removeTalk(QWidget *talk)
{
    int index = ui->stackedWidget->indexOf(talk);
    if(index>=0)
        ui->tabbar->removeTab(index);

    ui->stackedWidget->removeWidget(talk);
    p_d->talks.removeAll(talk);
}

void TalkManage::mergeTab(QWidget *tab,const QPoint &oldPos)
{
    if(!p_d->talks.contains(tab))
        p_d->talks.append(tab);

    if(isVisible())
    {
        QPoint pos = ui->tabbar->mapFromGlobal(QCursor::pos());
        if(ui->tabbar->rect().contains(pos))
        {
            int index = ui->tabbar->addTab(tab->objectName());
            ui->tabbar->setTabData(index,tab->objectName());
            ui->tabbar->setCurrentIndex(index);
            index = ui->stackedWidget->addWidget(tab);
            ui->stackedWidget->setCurrentIndex(index);
            p_d->currentWidget = tab;
        }
        else
        {
            tab->move(QCursor::pos()-oldPos);
            tab->show();
        }
    }
    else
    {
        tab->move(QCursor::pos()-oldPos);
        tab->show();
    }
}

QList<QWidget *> TalkManage::talks() const
{
    return p_d->talks;
}

QWidget *TalkManage::find(const QString &name)
{
    foreach(QWidget *w,p_d->talks)
    {
        if(w->objectName()==name)
            return w;
    }
    return 0;
}

void TalkManage::updateTalks()
{
    if(ui->tabbar->count()<=1)
    {
        ui->tabbar->removeTab(0);
        setVisible(false);
    }
    else
    {
        setVisible(true);
    }
}

void TalkManage::setCurrentWidget(QWidget *widget)
{
    p_d->currentWidget = widget;
}

QWidget *TalkManage::currentWidget() const
{
    return p_d->currentWidget;
}

void TalkManage::updateWidget()
{
}

void TalkManage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    p_d->drawWindowEdge(&painter);
    QWidget::paintEvent(event);
}

void TalkManage::mouseMoveEvent(QMouseEvent *event)
{
    p_d->mouseMoveEvent(event);
    QWidget::mouseMoveEvent(event);
}

void TalkManage::mousePressEvent(QMouseEvent *event)
{
    p_d->mousePressEvent(event);
    QWidget::mousePressEvent(event);
}

void TalkManage::mouseReleaseEvent(QMouseEvent *event)
{
    p_d->mouseReleaseEvent(event);
    QWidget::mouseReleaseEvent(event);
}

bool TalkManage::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==ui->tabbar)
        return p_d->tabbarEvent(event);

    if(watched==ui->input)
        p_d->inputEvent(event);

    return QWidget::eventFilter(watched,event);
}

bool TalkManage::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    p_d->nativeEvent(eventType,message,result);
    return QWidget::nativeEvent(eventType,message,result);
}

bool TalkManage::event(QEvent *event)
{
    if(event->type()==QEvent::User)
    {
        QPoint pos = ui->tabbar->mapFromGlobal(QCursor::pos());
        if(ui->tabbar->rect().contains(pos))
            QssLoader::load(ui->tabbar,"talkmanage-tabbar-dragin");
        else
            QssLoader::load(ui->tabbar,"talkmanage-tabbar-dragout");
    }
    return QWidget::event(event);
}

void TalkManage::currentTabChanged(int tab)
{
    ui->stackedWidget->setCurrentWidget(p_d->talks.at(tab));
    p_d->currentWidget = ui->stackedWidget->widget(tab);
}

void TalkManage::removeTab(int tab)
{
    qDebug() << "tab:" << tab << ui->stackedWidget->widget(tab);
    QString name = ui->tabbar->tabData(tab).toString();
    ui->tabbar->removeTab(tab);
    for(int i=0;i<ui->stackedWidget->count();i++)
    {
        QWidget *w = ui->stackedWidget->widget(i);
        if(w->objectName()==name)
        {
            ui->stackedWidget->removeWidget(w);
            p_d->currentWidget = ui->stackedWidget->currentWidget();
            w->setParent(0);
            if(ui->stackedWidget->count()==1)
            {
                p_d->currentWidget = ui->stackedWidget->widget(0);
                ui->stackedWidget->removeWidget(p_d->currentWidget);
                p_d->currentWidget->setParent(0);
                p_d->currentWidget->move(pos());
                p_d->currentWidget->show();
                setVisible(false);
            }
            return ;
        }
    }
}

void TalkManage::on_ctrl_toggled(bool checked)
{
    if(checked)
        showMaximized();
    else
        showNormal();
}

void TalkManage::on_tabbar_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu(ui->tabbar);
    menu.addAction(ui->actionDCFT);
    menu.addAction(ui->actionSCS);
    menu.exec(ui->tabbar->mapToGlobal(pos));
}

void TalkManage::on_close_clicked()
{
    if(ui->tabbar->count())
    {

    }
    QWidget::close();
}
