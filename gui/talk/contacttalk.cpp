#include "contacttalk.h"
#include "ui_contacttalk.h"
#include "ui_talkwarntip.h"

#include "talkmanage.h"
#include "expressionwidget.h"
#include "windowimpl.h"

#include <QDialog>
#include <QFileDialog>
#include <QImageReader>
#include <QMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QTimer>
#include <QUrl>
#include <QDebug>
#include <QListWidget>
#include <QFontDatabase>
#include <QColorDialog>
#include <QToolButton>
#include <QScrollBar>
#include <qssloader.h>
#include <QDrag>
#include <QMimeData>
#include <QDebug>
#include <QTextBlock>

#include "messageitem.h"
#include "messagerecord.h"
#include "talkwarntip.h"
#include "wmtrayicon.h"

#include <menu/menu.h>



#define E_M ExpresssionManage::manage()
#define F_M FontManage::manage()

class ContactTalkPrivate : public WindowImpl
{
public:
    ContactTalkPrivate(ContactTalk *parent)
        :WindowImpl(parent)
        ,p(parent)
        ,voiceAnimationTimerInterval(1000)
        ,voiceTimeLimit(60)
        ,voiceTime(0)
        ,maxItemCount(100)
    {
        voiceAnimationColor.append(QColor(0,255,0));
        voiceAnimationColor.append(QColor(0,85,0));
    }

    void init()
    {
        p->ui->setupUi(p);

        voiceAnimationTimer.setSingleShot(false);
        voiceAnimationTimer.setInterval(1000);

        QObject::connect(&voiceAnimationTimer,SIGNAL(timeout()),p,SLOT(recordingVoice()));

        p->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
        p->setAttribute(Qt::WA_TranslucentBackground);
        p->setAttribute(Qt::WA_Mapped);
        p->setMouseTracking(true);

        p->ui->tool->installEventFilter(p);

        QToolButton *send = new QToolButton;
        send->setPopupMode(QToolButton::MenuButtonPopup);
        send->setIcon(QIcon(":/res/talk/okl.png"));
        send->setFixedSize(55,35);
        QAction *a = p->ui->tool->insertWidget(p->ui->actionVoice,send);
        a->setVisible(true);
        QList<QAction *> list;
        QAction *local = new QAction("Send Local Pictures");
        list.append(local);
        send->addActions(list);
        QObject::connect(send,SIGNAL(clicked()),p,SLOT(selectLocalPicture()));

        /* Screenshot. */
        QToolButton *screenshot = new QToolButton;
        screenshot->setPopupMode(QToolButton::MenuButtonPopup);
        screenshot->setFixedSize(55,35);
        a = p->ui->tool->insertWidget(p->ui->actionMusic,screenshot);
        a->setVisible(true);
        list.clear();
        a = new QAction("Screenshot Ctrl+ATL+A");
        list.append(a);
        a = new QAction("Hide this window when capturing.");
        list.append(a);
        screenshot->addActions(list);
        QObject::connect(screenshot,SIGNAL(clicked()),p,SLOT(selectLocalPicture()));

        /* Font setting init. */
        p->ui->font_setting->setVisible(false);

        /* Voice widget init. */
        p->ui->voice->setVisible(false);

        /* Warn tip widget init. */
        tip = new TalkWarnTip(p->ui->msg_display);
        tip->setVisible(false);

        record = new MessageRecord;

        /* when init, set font_select hide. */
        p->ui->font_select->hide();

        p->ui->splitter->setStretchFactor(0,7);
        p->ui->splitter->setStretchFactor(1,1);

        /* init msg display. */
        p->ui->msg_display->setScene(new QGraphicsScene);
        p->ui->msg_display->installEventFilter(p);
        p->ui->msg_display->setSceneRect(0,0,p->ui->msg_display->width(),p->ui->msg_display->height()-5);

        /* more tips. */
        more = new MessageMoreItem;
        more->setVisible(false);
        more->setScene(p->ui->msg_display->scene());

        /* photos. */
        photo = new MessagePhotosItem;
        photo->setScene(p->ui->msg_display->scene());

        /* chatter. */
        chatter = new MessageChatterItem;
        chatter->setChatter("Today is sun day!");
        chatter->setScene(p->ui->msg_display->scene());

        /* filter input event. */
        p->ui->input->installEventFilter(p);
        QFont font = p->ui->input->font();
        font.setWeight(14);
        p->ui->input->setFont(font);

        /* send menu. */
        sendMenu = Menu::createMenu(p);
        QssLoader::load(sendMenu,"talk-send-menu");
        sendMenu->addAction(p->ui->actionEnterSend);
        sendMenu->addAction(p->ui->actionCEnterSend);

        /* record menu. */
        recordMenu = Menu::createMenu(p);
        QssLoader::load(recordMenu,"talk-record-menu");
        recordMenu->addAction(p->ui->actionSMR);
        recordMenu->addAction(p->ui->actionCM);
        recordMenu->addAction(p->ui->actionMM);

        /* filter icon event. */
        p->ui->icon->installEventFilter(p);
    }

    void parentChangedEvent(QEvent *event)
    {
        if(w_p->parentWidget())
        {
            p->ui->menu->setVisible(false);
            p->ui->ctrl->setVisible(false);
            p->ui->min->setVisible(false);
            p->ui->close->setVisible(false);
            p->ui->icon->setVisible(false);
        }
        else
        {
            p->ui->menu->setVisible(true);
            p->ui->ctrl->setVisible(true);
            p->ui->min->setVisible(true);
            p->ui->close->setVisible(true);
            p->ui->icon->setVisible(true);
        }
        WindowImpl::parentChangedEvent(event);
    }

    void voiceRecordDone(Ui::ContactTalk *ui)
    {
        voiceAnimationTimer.stop();
        voiceTime = 0;
        ui->send->setEnabled(false);
        ui->voice->setVisible(false);
        ui->voice->setValue(0);
    }

    void updateMessageItems()
    {
        volatile qreal height = 0;
        volatile qreal h = 0;
        int count = 0;
        if(!chatter->isEmpty())
        {
            chatter->setItemWidth(p->ui->msg_display->width());
            chatter->setPos(QPointF(0,height));

            height+=chatter->boundingRect().height();
            h+= chatter->boundingRect().height();

            qDebug() << "chatter:" << chatter->boundingRect() << height;
        }
        if(!photo->isEmpty())
        {
            photo->setItemWidth(p->ui->msg_display->width());
            photo->setPos(QPointF(0,height));

            height+=photo->boundingRect().height();
            h+= photo->boundingRect().height();

            qDebug() << "photo:" << photo->boundingRect() << height;
        }

        if(items.count())
        {
            more->setItemWidth(p->ui->msg_display->width());
            more->setPos(QPointF(0,height));

            height+=more->boundingRect().height();
            h+= more->boundingRect().height();

            qDebug() << "more:" << more->boundingRect() << height;
        }

        int itemWidth = p->ui->msg_display->width()-10-p->ui->msg_display->verticalScrollBar()->width();
        foreach(AbstractMessageItem *item,items)
        {
            qDebug() << "item" << item->boundingRect() << height;
            item->setItemWidth(itemWidth);
            item->setPos(QPointF(0,height));

            height+=item->boundingRect().height();
            h+= item->boundingRect().height();
            count++;
            if(count==maxItemCount)
                break;
        }
        if(h<(p->ui->msg_display->height()-5))
            h = p->ui->msg_display->height()-5;
        p->ui->msg_display->setSceneRect(0,0,p->ui->msg_display->width(),h);
        update();
    }

    void msgDisplayEvent(QEvent *event)
    {
        QGraphicsItem *clickedItem = 0;
        QWidget *w = p->ui->msg_display->viewport();
        switch(event->type())
        {
        case QEvent::MouseButtonPress:
            clickedItem = p->ui->msg_display->itemAt(w->mapFromGlobal(QCursor::pos()));
            if(clickedItem)
            {
                qDebug() << "item clicked";
                emit p->headClicked(clickedItem->data(AbstractMessageItem::Name).toString());
            }
            break;
        case QEvent::Resize:
            updateMessageItems();
            break;
        default:
            break;
        }
    }

    bool toolEvent(QEvent *event)
    {
        if(event->type()==QEvent::HoverEnter || event->type()==QEvent::HoverMove)
        {
            QPoint pos = p->ui->tool->mapFromGlobal(QCursor::pos());
            if(p->ui->tool->actionAt(pos)==p->ui->actionExpression && !p->ui->actionExpression->isChecked())
            {
                E_M->expression->hide();
                E_M->history->show(p->ui->tool->mapToGlobal(QPoint(0,5)));
            }
            else
                E_M->history->hide();
        }
        else if(event->type()==QEvent::HoverLeave)
        {
            if(!E_M->history->rect().contains(E_M->history->mapFromGlobal(QCursor::pos())))
                E_M->history->hide();
        }
        return false;
    }

    bool inputEvent(QEvent *event)
    {
        QKeyEvent *ke;
        switch(event->type())
        {
        case QEvent::KeyPress:
            ke = dynamic_cast<QKeyEvent *>(event);
            if(!ke)
                return false;

            switch(ke->key())
            {
            case Qt::Key_Return:
                if(p->ui->actionEnterSend->isChecked())
                {
                    p->send();
                    return true;
                }
                else
                {
                    if(ke->modifiers()==Qt::CTRL)
                    {
                        p->send();
                        return true;
                    }
                }
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        return false;
    }

    void iconEvent(QEvent *event)
    {
        QMouseEvent *me;
        static bool pressFlag = false;
        static bool moveFlag = false;
        static QPoint pos;
        switch(event->type())
        {
        case QEvent::MouseButtonRelease:
            me = static_cast<QMouseEvent *>(event);
            if(!me)
                return ;

            pressFlag = false;
            if(!moveFlag)
                return ;

            moveFlag = false;
            p->setWindowOpacity(1.0);
            qDebug() << "ready to merge tab";
            TalkManage::instance()->mergeTab(p,pos);
            break;
        case QEvent::MouseButtonPress:
            me = static_cast<QMouseEvent *>(event);
            if(!me)
                return ;

            pressFlag = true;
            pos = p->mapFromGlobal(QCursor::pos());
            break;
        case QEvent::MouseMove:
            me = static_cast<QMouseEvent *>(event);
            if(!me)
                return ;

            moveFlag = true;
            if(pressFlag)
            {
                qDebug() << "mouse move";
                p->setWindowOpacity(0);
            }
            QApplication::postEvent(TalkManage::instance(),new QEvent(QEvent::User));
            break;
        default:
            break;
        }
    }

    ContactTalk *p;
    QTimer voiceAnimationTimer;
    QList<QColor> voiceAnimationColor;
    int voiceAnimationTimerInterval;
    int voiceTimeLimit;
    int voiceTime;
    TalkWarnTip *tip;
    MessageRecord *record;

    QList<AbstractMessageItem *> items;
    MessageMoreItem *more;
    MessagePhotosItem *photo;
    MessageChatterItem *chatter;
    int maxItemCount;

    QMenu *sendMenu;
    QMenu *recordMenu;

    QSize size;
};

ContactTalk::ContactTalk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactTalk),
    p_d(new ContactTalkPrivate(this))
{
    p_d->init();
    setVisible(true);
    updateMessageItems();
}

ContactTalk::~ContactTalk()
{
    delete ui;
    delete p_d;
}

void ContactTalk::appendItem(AbstractMessageItem *item)
{
    p_d->items.append(item);
    if(p_d->items.count()>p_d->maxItemCount)
        p_d->more->setVisible(true);
    else
        p_d->more->setVisible(false);
    item->setScene(ui->msg_display->scene());
    updateMessageItems();
}

void ContactTalk::appendItems(const QList<AbstractMessageItem *> &items)
{
    p_d->items.append(items);

    foreach(AbstractMessageItem *item,items)
        item->setScene(ui->msg_display->scene());

    updateMessageItems();
}

void ContactTalk::prependItem(AbstractMessageItem *item)
{
    p_d->items.prepend(item);
    if(p_d->items.count()>p_d->maxItemCount)
        p_d->more->setVisible(true);
    else
        p_d->more->setVisible(false);

    item->setScene(ui->msg_display->scene());
    updateMessageItems();
}

void ContactTalk::prependItems(const QList<AbstractMessageItem *> &items)
{
    foreach(AbstractMessageItem *item,items)
    {
        p_d->items.prepend(item);
        item->setScene(ui->msg_display->scene());
    }

    updateMessageItems();
}

void ContactTalk::removeItem(AbstractMessageItem *item)
{
    p_d->items.removeAll(item);
    if(p_d->items.count()>p_d->maxItemCount)
        p_d->more->setVisible(true);
    else
        p_d->more->setVisible(false);

    updateMessageItems();
}

void ContactTalk::setMaxCount(int count)
{
    p_d->maxItemCount = count;
    updateMessageItems();
}

int ContactTalk::maxCount() const
{
    return p_d->maxItemCount;
}

void ContactTalk::setChatter(const QString &chatter)
{
    p_d->chatter->setChatter(chatter);
    if(chatter.isEmpty())
        p_d->chatter->setVisible(false);
    else
        p_d->chatter->setVisible(true);
}

QString ContactTalk::chatter() const
{
    return p_d->chatter->chatter();
}

void ContactTalk::setPhotos(const QStringList &photos)
{
    QList<QPixmap> list;
    foreach(QString photo,photos)
    {
        QPixmap pixmap(photo);
        if(!pixmap.isNull())
            list.append(pixmap);
    }
    p_d->photo->setPhotos(list);
    p_d->photo->setVisible(!list.isEmpty());
}

void ContactTalk::setPhotos(const QList<QPixmap> &photos)
{
    p_d->photo->setPhotos(photos);
}

QList<QPixmap> ContactTalk::photos()
{
    return p_d->photo->photos();
}

void ContactTalk::showWarning(const QString &warning)
{
    p_d->tip->pop(QSize(ui->msg_display->width(),p_d->tip->height()),warning);
}

void ContactTalk::updateMessageItems()
{
    p_d->updateMessageItems();
}

void ContactTalk::send()
{
    MessageTextItem *item = \
            new MessageTextItem(QPixmap(":/res/talk/icon.jpg"),"name","message",ui->input->document());
    item->setDirection(Qt::LeftToRight);
    appendItem(item);
    ui->input->clear();
    updateMessageItems();
}

void ContactTalk::expressionReset()
{
    if(ui->tool->actionAt(ui->tool->mapFromGlobal(QCursor::pos()))!=ui->actionExpression)
        ui->actionExpression->setChecked(false);
}

void ContactTalk::sysFontReset()
{
    ui->sys_font->setIcon(QIcon(":/res/talk/nnu.png"));
}

void ContactTalk::customFontReset()
{
    if(!ui->font_option->rect().contains(ui->font_option->mapFromGlobal(QCursor::pos())))
    {
        qDebug() << "custom font reset";
        ui->font_option->setIcon(QIcon(":/res/talk/nnu.png"));
        ui->font_option->setChecked(false);
//        F_M->m_customFontSelect->hide();
    }
}

void ContactTalk::textFontSizeReset()
{
    ui->font_size->setIcon(QIcon(":/res/talk/nnu.png"));
    ui->font_size->setChecked(false);
    //    F_M->m_customFontSelect->hide();
}

void ContactTalk::bubbleFontSizeReset()
{
    ui->bubble_font_size->setIcon(QIcon(":/res/talk/nnu.png"));
    ui->bubble_font_size->setChecked(false);
    //    F_M->m_customFontSelect->hide();
}

bool ContactTalk::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::ParentChange:
        p_d->parentChangedEvent(event);
        break;
    default:
        break;
    }
    return QWidget::event(event);
}

void ContactTalk::insertPixmap(QPixmap pixmap)
{
    qDebug() << "insert picture";
    QTextCursor cursor = ui->input->textCursor();
    cursor.insertImage(pixmap.toImage());
}

void ContactTalk::setFontSize(QString size)
{
    qDebug() << "setFontSize";
    ui->input->setFontPointSize(size.toInt() ? size.toInt() : ui->input->fontPointSize());
}

void ContactTalk::setFont(QString font)
{
    qDebug() << "setFont";
    ui->input->setFontFamily(font);
}

void ContactTalk::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    p_d->drawWindowEdge(&painter);
    QWidget::paintEvent(event);
}

void ContactTalk::mouseMoveEvent(QMouseEvent *event)
{
    p_d->mouseMoveEvent(event);
    QWidget::mouseMoveEvent(event);
}

void ContactTalk::mousePressEvent(QMouseEvent *event)
{
    p_d->mousePressEvent(event);
    if(childAt(event->pos()))
    {
        E_M->expression->hide();
        ui->actionExpression->setChecked(false);
    }
    QWidget::mousePressEvent(event);
}

void ContactTalk::mouseReleaseEvent(QMouseEvent *event)
{
    p_d->mouseReleaseEvent(event);
    QWidget::mouseReleaseEvent(event);
}

void ContactTalk::mouseDoubleClickEvent(QMouseEvent *event)
{
    p_d->mouseDoubleEvent(event);
    if(childAt(event->pos())==ui->top)
    {
        if(isMaximized())
            showNormal();
        else
            showMaximized();
    }
    QWidget::mouseDoubleClickEvent(event);
}

void ContactTalk::resizeEvent(QResizeEvent *event)
{
    p_d->tip->resize(ui->msg_display->width(),p_d->tip->height());
    updateMessageItems();
    QWidget::resizeEvent(event);
}

bool ContactTalk::eventFilter(QObject *watched, QEvent *event)
{
//    qDebug() << "aaaaa:" << watched << event->type();
    if(watched==ui->tool)
        return p_d->toolEvent(event);

    if(watched==ui->msg_display)
        p_d->msgDisplayEvent(event);

    if(watched==ui->input)
        return p_d->inputEvent(event);

    if(watched==ui->icon)
        p_d->iconEvent(event);

    return QWidget::eventFilter(watched,event);
}

void ContactTalk::focusOutEvent(QFocusEvent *event)
{
    QWidget::focusOutEvent(event);
}

void ContactTalk::focusInEvent(QFocusEvent *event)
{
    E_M->setTarget(this);
    F_M->setTarget(this);
    QWidget::focusInEvent(event);
}

void ContactTalk::showEvent(QShowEvent *event)
{
    E_M->setTarget(this);
    F_M->setTarget(this);
    QWidget::showEvent(event);
}

bool ContactTalk::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    p_d->nativeEvent(eventType,message,result);
    return QWidget::nativeEvent(eventType,message,result);
}

void ContactTalk::startRecordVoice()
{
    p_d->voiceAnimationTimer.start();
}

void ContactTalk::cancelRecordVoice()
{
    p_d->voiceRecordDone(ui);
}

void ContactTalk::endRecordVoice()
{
    p_d->voiceRecordDone(ui);
}

void ContactTalk::sendVoice()
{
    p_d->voiceRecordDone(ui);
}

void ContactTalk::recordingVoice()
{
    static int index = 0;
    if(index>(p_d->voiceAnimationColor.count()-1))
        index=0;

    QColor color = p_d->voiceAnimationColor.at(index++);
    {
        ui->light->setStyleSheet(QString("QLabel#light{"
        "border-radius:5px;border:1px solid gray;"
        "background-color:%1}").arg(color.name()));
    }
    p_d->voiceTime++;
    int percent = ((double)p_d->voiceTime/p_d->voiceTimeLimit)*100;

    if(percent>0)
        ui->voice_send->setEnabled(true);

    if(percent>100)
        percent = 100;

    ui->voice->setValue(percent);

    update();
    if(percent==100)
        endRecordVoice();
}

void ContactTalk::selectLocalPicture()
{
    QString file = QFileDialog::getOpenFileName(this,"Select Picture",QDir::homePath(),"*.png *.jpg");

    QImage image = QImageReader ( file ).read();
    QUrl url(file);
    QTextDocument *textDocument = ui->input->document();
    textDocument->addResource( QTextDocument::ImageResource,url, QVariant ( image ) );
    QTextCursor cursor = ui->input->textCursor();
    QTextImageFormat imageFormat;
    imageFormat.setWidth( image.width() );
    imageFormat.setHeight( image.height() );
    imageFormat.setName( file );
    cursor.insertImage(imageFormat);
}

void ContactTalk::on_actionFont_toggled(bool arg1)
{
    ui->font_setting->setVisible(arg1);
    if(arg1)
    {

    }
    else
    {}
}

void ContactTalk::on_actionVoice_triggered()
{
    if(ui->voice->isVisible())
    {
        showWarning("Voice is running, please wait for it run over and try it again!");
        return ;
    }
    ui->voice->setVisible(true);

    startRecordVoice();
}


void ContactTalk::on_voice_send_clicked()
{
    sendVoice();
}

void ContactTalk::on_voice_cancel_clicked()
{
    ui->voice->setVisible(false);
    cancelRecordVoice();
}

void ContactTalk::on_actionExpression_hovered()
{
//    history->show(ui->msg->mapToGlobal(QPoint(ui->msg->x(),ui->msg->height())));
}


void ContactTalk::on_actionExpression_toggled(bool arg1)
{
    Q_UNUSED(arg1)
}




void ContactTalk::on_bubble_toggled(bool checked)
{
    if(checked)
        ui->font_stacked->setCurrentWidget(ui->bubble_setting);
}

void ContactTalk::on_text_toggled(bool checked)
{
    if(checked)
        ui->font_stacked->setCurrentWidget(ui->text_setting);
}

/* bubble mode. */
void ContactTalk::on_bubble_font_toggled(bool checked)
{
    if(checked)
    {
        ui->bubble_font->setIcon(QIcon(":/res/talk/nnv.png"));
        F_M->customFont->move(ui->bubble_font->mapToGlobal(QPoint(0,ui->bubble_font->height())));
        F_M->customFont->show();
    }
    else
    {
        ui->bubble_font->setIcon(QIcon(":/res/talk/nnu.png"));
        F_M->customFont->hide();
    }
}

void ContactTalk::on_bubble_font_size_toggled(bool checked)
{
    if(checked)
    {
        ui->bubble_font_size->setIcon(QIcon(":/res/talk/nnv.png"));
        F_M->bubbleFontSize->resize(ui->bubble_font_size->width(),150);
        F_M->bubbleFontSize->move(ui->bubble_font_size->mapToGlobal(QPoint(0,ui->bubble_font_size->height())));
        F_M->bubbleFontSize->show();
    }
    else
    {
        ui->bubble_font_size->setIcon(QIcon(":/res/talk/nnu.png"));
        F_M->bubbleFontSize->hide();
    }
}

void ContactTalk::on_sys_font_toggled(bool checked)
{
    if(checked)
    {
        ui->font_select->hide();
        ui->font_option->setVisible(true);
    }
}

void ContactTalk::on_color_font_toggled(bool checked)
{
    if(checked)
    {
        ui->font_option->hide();
        ui->font_select->setVisible(true);
    }
}

/*
 * TextOptionSelect *m_customFontSelect;
    TextOptionSelect *m_bubbleFontSizeSelect;

    TextOptionSelect *m_sysFontSelect;
    TextOptionSelect *m_textFontSizeSelect;
*/

/* text mode. */
void ContactTalk::on_font_option_toggled(bool checked)
{
    Q_UNUSED(checked)
//    if(checked)
//    {
//        ui->font_option->setIcon(QIcon(":/res/talk/nnv.png"));
//        F_M->m_customFontSelect->resize(ui->font_option->width(),150);
//        F_M->m_customFontSelect->move(ui->font_option->mapToGlobal(QPoint(0,ui->font_option->height())));
//        F_M->m_customFontSelect->show();
//    }
//    else
//    {
//        ui->font_option->setIcon(QIcon(":/res/talk/nnu.png"));
//        F_M->m_customFontSelect->hide();
//    }
}

void ContactTalk::on_font_select_toggled(bool checked)
{
    if(checked)
    {
        ui->font_select->setIcon(QIcon(":/res/talk/nnv.png"));
        F_M->sysFont->resize(ui->font_select->width(),150);
        F_M->sysFont->move(ui->font_select->mapToGlobal(QPoint(0,ui->font_select->height())));
        F_M->sysFont->show();
    }
    else
    {
        ui->font_select->setIcon(QIcon(":/res/talk/nnu.png"));
        F_M->sysFont->hide();
    }
}

void ContactTalk::on_font_size_toggled(bool checked)
{
    if(checked)
    {
        ui->font_size->setIcon(QIcon(":/res/talk/nnv.png"));
        F_M->textFontSize->resize(ui->font_size->width(),150);
        F_M->textFontSize->move(ui->font_size->mapToGlobal(QPoint(0,ui->font_size->height())));
        F_M->textFontSize->show();
    }
    else
    {
        ui->font_size->setIcon(QIcon(":/res/talk/nnu.png"));
        F_M->textFontSize->hide();
    }
}

void ContactTalk::on_bold_toggled(bool checked)
{
    Q_UNUSED(checked)
}

void ContactTalk::on_italic_toggled(bool checked)
{
    ui->input->setFontItalic(checked);
}

void ContactTalk::on_underline_toggled(bool checked)
{
    ui->input->setFontUnderline(checked);
}



void ContactTalk::on_actionExpression_triggered(bool checked)
{
    E_M->history->hide();

    if(checked)
        E_M->expression->animationShow(E_M->history->size(),E_M->expression->size(),ui->tool->mapToGlobal(QPoint(0,0)));
    else
        E_M->expression->setVisible(false);
}

void ContactTalk::on_font_option_pressed()
{
    qDebug() << "font option" << ui->font_option->isChecked();
    if(!ui->font_option->isChecked())
    {
        ui->font_option->setChecked(true);
        ui->font_option->setIcon(QIcon(":/res/talk/nnv.png"));
        F_M->customFont->resize(ui->font_option->width(),150);
        F_M->customFont->move(ui->font_option->mapToGlobal(QPoint(0,ui->font_option->height())));
        F_M->customFont->show();
    }
    else
    {
        ui->font_option->setChecked(true);
        ui->font_option->setIcon(QIcon(":/res/talk/nnu.png"));
        F_M->customFont->hide();
    }
}

void ContactTalk::on_color_option_clicked()
{
    QTextCharFormat fmt = ui->input->currentCharFormat();
    QColor color = QColorDialog::getColor(fmt.foreground().color(),this,"Choose Color");
    fmt.setForeground(color);
    QTextCursor cursor = ui->input->textCursor();
    cursor.mergeCharFormat(fmt);
    ui->input->mergeCurrentCharFormat(fmt);
}


//void ContactTalk::on_log_toggled(bool checked)
//{
//    if(checked)
//    {
//        ui->right->addTab(p_d->record,"Message Record");
//    }
//    else
//    {}
//}

void ContactTalk::on_right_tabCloseRequested(int index)
{
    ui->right->removeTab(index);
}

void ContactTalk::on_actionEnterSend_triggered()
{
    ui->actionCEnterSend->setChecked(false);
    ui->actionEnterSend->setChecked(true);
}

void ContactTalk::on_actionCEnterSend_triggered()
{
    ui->actionCEnterSend->setChecked(true);
    ui->actionEnterSend->setChecked(false);
}

void ContactTalk::on_send_menu_clicked()
{
    QPoint p = ui->send_menu->rect().bottomLeft();
    QPoint pos = ui->send_menu->mapToGlobal(p);
    p_d->sendMenu->exec(pos);
}

void ContactTalk::on_record_menu_clicked()
{
    QPoint p = ui->record_menu->rect().bottomLeft();
    QPoint pos = ui->record_menu->mapToGlobal(p);
    p_d->recordMenu->exec(pos);
}

void ContactTalk::on_ctrl_toggled(bool checked)
{
    if(checked)
        showMaximized();
    else
        showNormal();
}
