#include "talkwindow.h"
#include "ui_talkwindow.h"
#include "ui_talkwindowwarntip.h"

#include "expressionwidget.h"
#include "toolbaraction.h"
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

#include "messagerecord.h"
#include "wmtrayicon.h"

class ExpresssionManage
{
public:
    ~ExpresssionManage()
    {
        delete history;
        delete expression;
    }
    static ExpresssionManage *manage()
    {
        if(!e_m)
            e_m = new ExpresssionManage;

        return e_m;
    }
    void setTarget(TalkWindow *talk)
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
        if(talk)
            talk->expressionReset();

        target = talk;
        QObject::connect(expression,SIGNAL(selectedExpression(QPixmap)),talk,SLOT(insertPixmap(QPixmap)));
        QObject::connect(expression,SIGNAL(aboutToHide()),talk,SLOT(expressionReset()));
    }
    bool isCurrentTarget(TalkWindow *current)
    {
        return (target == current);
    }
    ExpressionHistory *history;
    ExpressionWidget *expression;
protected:
    ExpresssionManage()
        :target(0)
    {
        history = new ExpressionHistory;
        expression = new ExpressionWidget;
    }
    static ExpresssionManage *e_m;
    TalkWindow *target;
};

ExpresssionManage *ExpresssionManage::e_m = 0;

#define E_M ExpresssionManage::manage()

class FontManage
{
public:
    ~FontManage()
    {
        delete customFont;
        delete bubbleFontSize;
        delete sysFont;
        delete textFontSize;
    }

    static FontManage *manage()
    {
        if(!f_m)
            f_m = new FontManage;
        return f_m;
    }
    void setTarget(TalkWindow *talk)
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
    bool isCurrentTarget(TalkWindow *current)
    {
        return (target == current);
    }

    TextOptionSelect *customFont;
    TextOptionSelect *bubbleFontSize;

    TextOptionSelect *sysFont;
    TextOptionSelect *textFontSize;

protected:
    FontManage()
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
private:
    static FontManage *f_m;
    TalkWindow *target;
};

FontManage *FontManage::f_m = 0;

#define F_M FontManage::manage()


class TalkWindowPrivate : public WindowImpl
{
public:
    TalkWindowPrivate(TalkWindow *parent)
        :WindowImpl(parent)
        ,p(parent)
        ,voiceAnimationTimerInterval(1000)
        ,voiceTimeLimit(60)
        ,voiceTime(0)
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
        tip = new TalkWindowWarnTip(p->ui->msg);
        tip->setVisible(false);

        record = new MessageRecord;

        /* when init, set font_select hide. */
        p->ui->font_select->hide();

        p->ui->splitter->setStretchFactor(0,7);
        p->ui->splitter->setStretchFactor(1,1);
    }

    void voiceRecordDone(Ui::TalkWindow *ui)
    {
        voiceAnimationTimer.stop();
        voiceTime = 0;
        ui->send->setEnabled(false);
        ui->voice->setVisible(false);
        ui->voice->setValue(0);
    }

    TalkWindow *p;
    QTimer voiceAnimationTimer;
    QList<QColor> voiceAnimationColor;
    int voiceAnimationTimerInterval;
    int voiceTimeLimit;
    int voiceTime;
    TalkWindowWarnTip *tip;
    MessageRecord *record;
};

TalkWindow::TalkWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TalkWindow),
    p_d(new TalkWindowPrivate(this))
{
    p_d->init();
}

TalkWindow::~TalkWindow()
{
    delete ui;
    delete p_d;
}

void TalkWindow::showWarning(const QString &warning)
{
    p_d->tip->pop(QSize(ui->msg->width(),p_d->tip->height()),warning);
}

void TalkWindow::expressionReset()
{
    if(ui->tool->actionAt(ui->tool->mapFromGlobal(QCursor::pos()))!=ui->actionExpression)
        ui->actionExpression->setChecked(false);
}

void TalkWindow::sysFontReset()
{
    ui->sys_font->setIcon(QIcon(":/res/talk/nnu.png"));
//    ui->sys_font->
//    F_M->m_sysFontSelect->hide();
}

void TalkWindow::customFontReset()
{
    if(!ui->font_option->rect().contains(ui->font_option->mapFromGlobal(QCursor::pos())))
    {
        qDebug() << "custom font reset";
        ui->font_option->setIcon(QIcon(":/res/talk/nnu.png"));
        ui->font_option->setChecked(false);
//        F_M->m_customFontSelect->hide();
    }
}

void TalkWindow::textFontSizeReset()
{
    ui->font_size->setIcon(QIcon(":/res/talk/nnu.png"));
    ui->font_size->setChecked(false);
    //    F_M->m_customFontSelect->hide();
}

void TalkWindow::bubbleFontSizeReset()
{
    ui->bubble_font_size->setIcon(QIcon(":/res/talk/nnu.png"));
    ui->bubble_font_size->setChecked(false);
    //    F_M->m_customFontSelect->hide();
}

void TalkWindow::insertPixmap(QPixmap pixmap)
{
    qDebug() << "insert picture";
    QTextCursor cursor = ui->input->textCursor();
    cursor.insertImage(pixmap.toImage());
}

void TalkWindow::setFontSize(QString size)
{
    qDebug() << "setFontSize";
    ui->input->setFontPointSize(size.toInt() ? size.toInt() : ui->input->fontPointSize());
}

void TalkWindow::setFont(QString font)
{
    qDebug() << "setFont";
    ui->input->setFontFamily(font);
}

void TalkWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    p_d->drawWindowEdge(&painter);
    QWidget::paintEvent(event);
}

void TalkWindow::mouseMoveEvent(QMouseEvent *event)
{
    p_d->mouseMoveEvent(event);
    QWidget::mouseMoveEvent(event);
}

void TalkWindow::mousePressEvent(QMouseEvent *event)
{
    p_d->mousePressEvent(event);
    if(childAt(event->pos()))
    {
        E_M->expression->hide();
        ui->actionExpression->setChecked(false);
    }
    QWidget::mousePressEvent(event);
}

void TalkWindow::mouseReleaseEvent(QMouseEvent *event)
{
    p_d->mouseReleaseEvent(event);
    QWidget::mouseReleaseEvent(event);
}

void TalkWindow::mouseDoubleClickEvent(QMouseEvent *event)
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

void TalkWindow::resizeEvent(QResizeEvent *event)
{
    p_d->tip->resize(ui->msg->width(),p_d->tip->height());
    QWidget::resizeEvent(event);
}

bool TalkWindow::eventFilter(QObject *watched, QEvent *event)
{
    qDebug() << "aaaaa:" << watched << event->type();
    if(watched==ui->tool)
    {
        if(event->type()==QEvent::HoverEnter || event->type()==QEvent::HoverMove)
        {
            QPoint p = ui->tool->mapFromGlobal(QCursor::pos());
            if(ui->tool->actionAt(p)==ui->actionExpression && !ui->actionExpression->isChecked())
            {
                E_M->expression->hide();
                E_M->history->show(ui->tool->mapToGlobal(QPoint(0,5)));
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

    return QWidget::eventFilter(watched,event);
}

void TalkWindow::focusOutEvent(QFocusEvent *event)
{
    QWidget::focusOutEvent(event);
}

void TalkWindow::focusInEvent(QFocusEvent *event)
{
    E_M->setTarget(this);
    F_M->setTarget(this);
    QWidget::focusInEvent(event);
}

void TalkWindow::showEvent(QShowEvent *event)
{
    E_M->setTarget(this);
    F_M->setTarget(this);
    QWidget::showEvent(event);
}

void TalkWindow::startRecordVoice()
{
    p_d->voiceAnimationTimer.start();
}

void TalkWindow::cancelRecordVoice()
{
    p_d->voiceRecordDone(ui);
}

void TalkWindow::endRecordVoice()
{
    p_d->voiceRecordDone(ui);
}

void TalkWindow::sendVoice()
{
    p_d->voiceRecordDone(ui);
}

void TalkWindow::recordingVoice()
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

void TalkWindow::selectLocalPicture()
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

void TalkWindow::on_radioButton_2_toggled(bool checked)
{
    if(checked)
        showMaximized();
    else
        showNormal();
}

void TalkWindow::on_actionFont_toggled(bool arg1)
{
    ui->font_setting->setVisible(arg1);
    if(arg1)
    {

    }
    else
    {}
}

void TalkWindow::on_actionVoice_triggered()
{
    if(ui->voice->isVisible())
    {
        showWarning("Voice is running, please wait for it run over and try it again!");
        return ;
    }
    ui->voice->setVisible(true);

    startRecordVoice();
}

TalkWindowWarnTip::TalkWindowWarnTip(QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::TalkWindowWarnTip)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->setInterval(1000*5);
    timer->setSingleShot(true);
    connect(timer,SIGNAL(timeout()),this,SLOT(hide()));
    connect(ui->close,SIGNAL(clicked(bool)),this,SLOT(hide()));
}

TalkWindowWarnTip::~TalkWindowWarnTip()
{
    delete ui;
}

void TalkWindowWarnTip::setWarnText(const QString &text)
{
    ui->warn->setText(text);
}

QString TalkWindowWarnTip::warnText() const
{
    return ui->warn->text();
}

void TalkWindowWarnTip::pop(const QSize &size,const QString &warning)
{
    if(!isVisible())
    {
        setWarnText(warning);
        setVisible(true);
    }
    resize(size);
    timer->start();
}

void TalkWindowWarnTip::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(),QColor(129, 194, 255));
    QWidget::paintEvent(event);
}


void TalkWindow::on_voice_send_clicked()
{
    sendVoice();
}

void TalkWindow::on_voice_cancel_clicked()
{
    ui->voice->setVisible(false);
    cancelRecordVoice();
}

void TalkWindow::on_actionExpression_hovered()
{
//    history->show(ui->msg->mapToGlobal(QPoint(ui->msg->x(),ui->msg->height())));
}


void TalkWindow::on_actionExpression_toggled(bool arg1)
{
    Q_UNUSED(arg1)
}

TextOptionSelect::TextOptionSelect(QWidget *parent)
    :QListWidget(parent)
{
    connect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(clickedSlot(QListWidgetItem*)));

    setStyleSheet("QListWidget{background-color:white;"
                  "border:2px solid rgb(26, 156, 255);"
                  "border-radius:4px;}QListWidget::item:hover"
                  "{background-color:rgb(26, 156, 255);}"
                  "QScrollBar::add-page{background-color: white;}"
                  "QScrollBar::add-page:hover{background-color: lightgray;}"
                  "QScrollBar::sub-page{background-color: white;}"
                  "QScrollBar::sub-page:hover{background-color: lightgray;}"
                  "QScrollBar:vertical {border: none;width: 10px;border-radius:1px;}"
                  "QScrollBar::handle:vertical{background: rgb(232, 232, 232);border-radius:5px;min-height: 20px;}"
                  "QScrollBar::handle:vertical:hover{background: rgb(149, 149, 149);}");

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


void TalkWindow::on_bubble_toggled(bool checked)
{
    if(checked)
        ui->font_stacked->setCurrentWidget(ui->bubble_setting);
}

void TalkWindow::on_text_toggled(bool checked)
{
    if(checked)
        ui->font_stacked->setCurrentWidget(ui->text_setting);
}

/* bubble mode. */
void TalkWindow::on_bubble_font_toggled(bool checked)
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

void TalkWindow::on_bubble_font_size_toggled(bool checked)
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

void TalkWindow::on_sys_font_toggled(bool checked)
{
    if(checked)
    {
        ui->font_select->hide();
        ui->font_option->setVisible(true);
    }
}

void TalkWindow::on_color_font_toggled(bool checked)
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
void TalkWindow::on_font_option_toggled(bool checked)
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

void TalkWindow::on_font_select_toggled(bool checked)
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

void TalkWindow::on_font_size_toggled(bool checked)
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

void TalkWindow::on_bold_toggled(bool checked)
{
    Q_UNUSED(checked)
}

void TalkWindow::on_italic_toggled(bool checked)
{
    ui->input->setFontItalic(checked);
}

void TalkWindow::on_underline_toggled(bool checked)
{
    ui->input->setFontUnderline(checked);
}

BubbleFontSelect::BubbleFontSelect(QWidget *parent)
    :QWidget(parent)
{

}

BubbleFontSelect::~BubbleFontSelect()
{

}

void TalkWindow::on_actionExpression_triggered(bool checked)
{
    E_M->history->hide();

    if(checked)
        E_M->expression->animationShow(E_M->history->size(),E_M->expression->size(),ui->tool->mapToGlobal(QPoint(0,0)));
    else
        E_M->expression->setVisible(false);
}

void TalkWindow::on_font_option_pressed()
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

void TalkWindow::on_color_option_clicked()
{
    QTextCharFormat fmt = ui->input->currentCharFormat();
    QColor color = QColorDialog::getColor(fmt.foreground().color(),this,"Choose Color");
    fmt.setForeground(color);
    QTextCursor cursor = ui->input->textCursor();
    cursor.mergeCharFormat(fmt);
    ui->input->mergeCurrentCharFormat(fmt);
}


void TalkWindow::on_log_toggled(bool checked)
{
    if(checked)
    {
        ui->right->addTab(p_d->record,"Message Record");
    }
    else
    {}
}

void TalkWindow::on_right_tabCloseRequested(int index)
{
    ui->right->removeTab(index);
}
