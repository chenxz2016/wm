#include "talkwidget.h"
#include "ui_talkwidget.h"
#include "ui_talkwidgetwarntip.h"

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
    void setCurrentWidget(TalkWidget *talk)
    {
        if(m_parent==talk)
            return ;

        if(m_parent)
        {
            QObject::disconnect(expression,SIGNAL(selectedExpression(QPixmap)),m_parent,SLOT(insertPixmap(QPixmap)));
            QObject::disconnect(expression,SIGNAL(aboutToHide()),m_parent,SLOT(expressionReset()));
        }
        expression->hide();
        history->hide();
        if(talk)
            talk->expressionReset();

        m_parent = talk;
        QObject::connect(expression,SIGNAL(selectedExpression(QPixmap)),talk,SLOT(insertPixmap(QPixmap)));
        QObject::connect(expression,SIGNAL(aboutToHide()),talk,SLOT(expressionReset()));
    }
    bool isCurrentWidget(TalkWidget *current)
    {
        return (m_parent == current);
    }
    ExpressionHistory *history;
    ExpressionWidget *expression;
    bool m_expressionShowing;
protected:
    ExpresssionManage()
        :m_expressionShowing(false)
        ,m_parent(0)
    {
        history = new ExpressionHistory;
        expression = new ExpressionWidget;
    }
    static ExpresssionManage *e_m;
    TalkWidget *m_parent;

};

ExpresssionManage *ExpresssionManage::e_m = 0;

#define E_M ExpresssionManage::manage()

class FontManage
{
public:
    ~FontManage()
    {
        delete m_customFontSelect;
        delete m_bubbleFontSizeSelect;
        delete m_sysFontSelect;
        delete m_textFontSizeSelect;
    }

    static FontManage *manage()
    {
        if(!f_m)
            f_m = new FontManage;
        return f_m;
    }
    void setCurrentWidget(TalkWidget *talk)
    {
        if(m_parent==talk)
            return ;

        if(m_parent)
        {
            QObject::disconnect(m_customFontSelect,SIGNAL(select(QString)),m_parent,SLOT(setFont(QString)));
            QObject::disconnect(m_customFontSelect,SIGNAL(aboutToHide()),m_parent,SLOT(customFontReset()));
            QObject::disconnect(m_bubbleFontSizeSelect,SIGNAL(select(QString)),m_parent,SLOT(setFontSize(QString)));
            QObject::disconnect(m_bubbleFontSizeSelect,SIGNAL(aboutToHide()),m_parent,SLOT(bubbleFontSizeReset()));
            QObject::disconnect(m_sysFontSelect,SIGNAL(select(QString)),m_parent,SLOT(setFont(QString)));
            QObject::disconnect(m_sysFontSelect,SIGNAL(aboutToHide()),m_parent,SLOT(sysFontReset()));
            QObject::disconnect(m_textFontSizeSelect,SIGNAL(select(QString)),m_parent,SLOT(setFontSize(QString)));
            QObject::disconnect(m_textFontSizeSelect,SIGNAL(aboutToHide()),m_parent,SLOT(textFontSizeReset()));
        }

        m_customFontSelect->hide();
        m_bubbleFontSizeSelect->hide();
        m_sysFontSelect->hide();
        m_textFontSizeSelect->hide();

        m_parent = talk;
        QObject::connect(m_customFontSelect,SIGNAL(select(QString)),m_parent,SLOT(setFont(QString)));
        QObject::connect(m_customFontSelect,SIGNAL(aboutToHide()),m_parent,SLOT(customFontReset()));
        QObject::connect(m_bubbleFontSizeSelect,SIGNAL(select(QString)),m_parent,SLOT(setFontSize(QString)));
        QObject::connect(m_bubbleFontSizeSelect,SIGNAL(aboutToHide()),m_parent,SLOT(bubbleFontSizeReset()));
        QObject::connect(m_sysFontSelect,SIGNAL(select(QString)),m_parent,SLOT(setFont(QString)));
        QObject::connect(m_sysFontSelect,SIGNAL(aboutToHide()),m_parent,SLOT(sysFontReset()));
        QObject::connect(m_textFontSizeSelect,SIGNAL(select(QString)),m_parent,SLOT(setFontSize(QString)));
        QObject::connect(m_textFontSizeSelect,SIGNAL(aboutToHide()),m_parent,SLOT(textFontSizeReset()));
    }
    bool isCurrentWidget(TalkWidget *current)
    {
        return (m_parent == current);
    }

    TextOptionSelect *m_customFontSelect;
    TextOptionSelect *m_bubbleFontSizeSelect;

    TextOptionSelect *m_sysFontSelect;
    TextOptionSelect *m_textFontSizeSelect;

protected:
    FontManage()
        :m_parent(0)
    {
        m_customFontSelect = new TextOptionSelect;
        QFontDatabase base;
        m_customFontSelect->addItems(base.families());

        m_sysFontSelect = new TextOptionSelect;
        m_sysFontSelect->addItems(base.families());

        m_bubbleFontSizeSelect = new TextOptionSelect;
        for(int i=9;i<14;i++)
            m_bubbleFontSizeSelect->addItem(QString::number(i));

        m_textFontSizeSelect = new TextOptionSelect;
        for(int i=9;i<22;i++)
            m_textFontSizeSelect->addItem(QString::number(i));
    }
private:
    static FontManage *f_m;
    TalkWidget *m_parent;
};

FontManage *FontManage::f_m = 0;

#define F_M                     FontManage::manage()


class TalkWidgetPrivate : public WindowImpl
{
public:
    TalkWidgetPrivate(TalkWidget *parent)
        :WindowImpl(parent)
        ,m_voiceAnimationTimerInterval(1000)
        ,m_voiceTimeLimit(60)
        ,m_voiceTime(0)
        ,m_enterFlag(false)
    {
        m_voiceAnimationTimer = new QTimer;
        m_voiceAnimationTimer->setSingleShot(false);
        m_voiceAnimationTimer->setInterval(1000);
        m_voiceAnimationColor.append(QColor(0,255,0));
        m_voiceAnimationColor.append(QColor(0,85,0));
    }

    void voiceRecordDone(Ui::TalkWidget *ui);

    QTimer *m_voiceAnimationTimer;
    QList<QColor> m_voiceAnimationColor;
    int m_voiceAnimationTimerInterval;
    int m_voiceTimeLimit;
    int m_voiceTime;
    bool m_enterFlag;
};

TalkWidget::TalkWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TalkWidget)
{
    p_d = new TalkWidgetPrivate(this);
    connect(p_d->m_voiceAnimationTimer,SIGNAL(timeout()),this,SLOT(recordingVoice()));

    ui->setupUi(this);
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_Mapped);
    setMouseTracking(true);
    ui->tool->installEventFilter(this);
//    ui->option->installEventFilter(this);
//    ui->input->installEventFilter(this);

    ToolBarAction *action = new ToolBarAction;
    action->setFixedSize(55,35);
    QAction *a = ui->tool->insertWidget(ui->actionVoice,action);
    a->setVisible(true);
    QList<QAction *> list;
    QAction *local = new QAction("Send Local Pictures");
    list.append(local);
    action->addActions(list);
    connect(action,SIGNAL(clicked()),this,SLOT(selectLocalPicture()));


    /* Screenshot. */
    action = new ToolBarAction;
    action->setFixedSize(55,35);
    a = ui->tool->insertWidget(ui->actionMusic,action);
    a->setVisible(true);
    list.clear();
    a = new QAction("Screenshot Ctrl+ATL+A");
    list.append(a);
    a = new QAction("Hide this window when capturing.");
    list.append(a);
    action->addActions(list);
    connect(action,SIGNAL(clicked()),this,SLOT(selectLocalPicture()));

    /* Font setting init. */
    ui->font_setting->setVisible(false);

    /* Voice widget init. */
    ui->voice->setVisible(false);

    /* Warn tip widget init. */
    tip = new TalkWidgetWarnTip(ui->msg);
    setAutoFillBackground(false);
    tip->setVisible(false);

    /* when init, set font_select hide. */
    ui->font_select->hide();
}

TalkWidget::~TalkWidget()
{
    delete p_d;
}

QColor TalkWidget::bgColor() const
{
    return p_d->bgColor;
}

void TalkWidget::setBgColor(const QColor &color)
{
    p_d->bgColor = color;
    p_d->update();
}

int TalkWidget::borderWidth() const
{
    return p_d->borderWidth;
}

void TalkWidget::setBorderWidth(int w)
{
    if(w<0 || (2*w) > width() || (2*w) > height() )
        return ;

    p_d->borderWidth = w;
    ui->mainLayout->setMargin(w);
    p_d->update();
}

QColor TalkWidget::borderColor() const
{
    return p_d->borderColor;
}

void TalkWidget::setBorderColor(const QColor &color)
{
    p_d->borderColor = color;
    p_d->update();
}

void TalkWidget::showWarning(const QString &warning)
{
    tip->pop(QSize(ui->msg->width(),tip->height()),warning);
}

void TalkWidget::expressionReset()
{
    if(ui->tool->actionAt(ui->tool->mapFromGlobal(QCursor::pos()))!=ui->actionExpression)
        ui->actionExpression->setChecked(false);
}

void TalkWidget::sysFontReset()
{
    ui->sys_font->setIcon(QIcon(":/res/talk/nnu.png"));
//    ui->sys_font->
//    F_M->m_sysFontSelect->hide();
}

void TalkWidget::customFontReset()
{
    if(!ui->font_option->rect().contains(ui->font_option->mapFromGlobal(QCursor::pos())))
    {
        qDebug() << "custom font reset";
        ui->font_option->setIcon(QIcon(":/res/talk/nnu.png"));
        ui->font_option->setChecked(false);
//        F_M->m_customFontSelect->hide();
    }
}

void TalkWidget::textFontSizeReset()
{
    ui->font_size->setIcon(QIcon(":/res/talk/nnu.png"));
    ui->font_size->setChecked(false);
    //    F_M->m_customFontSelect->hide();
}

void TalkWidget::bubbleFontSizeReset()
{
    ui->bubble_font_size->setIcon(QIcon(":/res/talk/nnu.png"));
    ui->bubble_font_size->setChecked(false);
    //    F_M->m_customFontSelect->hide();
}

void TalkWidget::insertPixmap(QPixmap pixmap)
{
    qDebug() << "insert picture";
    QTextCursor cursor = ui->input->textCursor();
    cursor.insertImage(pixmap.toImage());
}

void TalkWidget::setFontSize(QString size)
{
    qDebug() << "setFontSize";
    ui->input->setFontPointSize(size.toInt() ? size.toInt() : ui->input->fontPointSize());
}

void TalkWidget::setFont(QString font)
{
    qDebug() << "setFont";
    ui->input->setFontFamily(font);
}

void TalkWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    p_d->drawWindowEdge(&painter);
    QWidget::paintEvent(event);
}

void TalkWidget::mouseMoveEvent(QMouseEvent *event)
{
    p_d->mouseMoveEvent(event);
    QWidget::mouseMoveEvent(event);
}

void TalkWidget::mousePressEvent(QMouseEvent *event)
{
    p_d->mousePressEvent(event);
    if(childAt(event->pos()))
    {
        E_M->expression->hide();
        ui->actionExpression->setChecked(false);
    }
    QWidget::mousePressEvent(event);
}

void TalkWidget::mouseReleaseEvent(QMouseEvent *event)
{
    p_d->mouseReleaseEvent(event);
    QWidget::mouseReleaseEvent(event);
}

void TalkWidget::mouseDoubleClickEvent(QMouseEvent *event)
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

void TalkWidget::enterEvent(QEvent *event)
{
//    E_M->setCurrentWidget(this);
//    F_M->setCurrentWidget(this);
    p_d->m_enterFlag = true;
    QWidget::enterEvent(event);
}

void TalkWidget::leaveEvent(QEvent *event)
{
    p_d->m_enterFlag = false;
    QWidget::leaveEvent(event);
}

void TalkWidget::resizeEvent(QResizeEvent *event)
{
    tip->resize(ui->msg->width(),tip->height());
    QWidget::resizeEvent(event);
}

bool TalkWidget::eventFilter(QObject *watched, QEvent *event)
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

void TalkWidget::focusOutEvent(QFocusEvent *event)
{

    QWidget::focusOutEvent(event);
}

void TalkWidget::focusInEvent(QFocusEvent *event)
{
    E_M->setCurrentWidget(this);
    F_M->setCurrentWidget(this);
    QWidget::focusInEvent(event);
}

void TalkWidget::showEvent(QShowEvent *event)
{
    E_M->setCurrentWidget(this);
    F_M->setCurrentWidget(this);
    QWidget::showEvent(event);
}

void TalkWidget::startRecordVoice()
{
    p_d->m_voiceAnimationTimer->start();
}

void TalkWidget::cancelRecordVoice()
{
    p_d->voiceRecordDone(ui);
}

void TalkWidget::endRecordVoice()
{
    p_d->voiceRecordDone(ui);
}

void TalkWidget::sendVoice()
{
    p_d->voiceRecordDone(ui);
}

void TalkWidget::recordingVoice()
{
    static int index = 0;
    if(index>(p_d->m_voiceAnimationColor.count()-1))
        index=0;

    QColor color = p_d->m_voiceAnimationColor.at(index++);
    {
        ui->light->setStyleSheet(QString("QLabel#light{"
        "border-radius:5px;border:1px solid gray;"
        "background-color:%1}").arg(color.name()));
    }
    p_d->m_voiceTime++;
    int percent = ((double)p_d->m_voiceTime/p_d->m_voiceTimeLimit)*100;

    if(percent>0)
        ui->voice_send->setEnabled(true);

    if(percent>100)
        percent = 100;

    ui->voice->setValue(percent);

    update();
    if(percent==100)
        endRecordVoice();
}

void TalkWidget::selectLocalPicture()
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

void TalkWidget::on_radioButton_2_toggled(bool checked)
{
    if(checked)
        showMaximized();
    else
        showNormal();
}

void TalkWidget::on_actionFont_toggled(bool arg1)
{
    ui->font_setting->setVisible(arg1);
    if(arg1)
    {

    }
    else
    {}
}

void TalkWidget::on_actionVoice_triggered()
{
    if(ui->voice->isVisible())
    {
        showWarning("Voice is running, please wait for it run over and try it again!");
        return ;
    }
    ui->voice->setVisible(true);

    startRecordVoice();
}

TalkWidgetWarnTip::TalkWidgetWarnTip(QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::TalkWidgetWarnTip)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->setInterval(1000*5);
    timer->setSingleShot(true);
    connect(timer,SIGNAL(timeout()),this,SLOT(hide()));
    connect(ui->close,SIGNAL(clicked(bool)),this,SLOT(hide()));
}

TalkWidgetWarnTip::~TalkWidgetWarnTip()
{
    delete ui;
}

void TalkWidgetWarnTip::setWarnText(const QString &text)
{
    ui->warn->setText(text);
}

QString TalkWidgetWarnTip::warnText() const
{
    return ui->warn->text();
}

void TalkWidgetWarnTip::pop(const QSize &size,const QString &warning)
{
    if(!isVisible())
    {
        setWarnText(warning);
        setVisible(true);
    }
    resize(size);
    timer->start();
}

void TalkWidgetWarnTip::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(),QColor(129, 194, 255));
    QWidget::paintEvent(event);
}


void TalkWidget::on_voice_send_clicked()
{
    sendVoice();
}

void TalkWidget::on_voice_cancel_clicked()
{
    ui->voice->setVisible(false);
    cancelRecordVoice();
}

void TalkWidgetPrivate::voiceRecordDone(Ui::TalkWidget *ui)
{
    m_voiceAnimationTimer->stop();
    m_voiceTime = 0;
    ui->send->setEnabled(false);
    ui->voice->setVisible(false);
    ui->voice->setValue(0);
}

void TalkWidget::on_actionExpression_hovered()
{
//    history->show(ui->msg->mapToGlobal(QPoint(ui->msg->x(),ui->msg->height())));
}


void TalkWidget::on_actionExpression_toggled(bool arg1)
{

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


void TalkWidget::on_bubble_toggled(bool checked)
{
    if(checked)
        ui->font_stacked->setCurrentWidget(ui->bubble_setting);
}

void TalkWidget::on_text_toggled(bool checked)
{
    if(checked)
        ui->font_stacked->setCurrentWidget(ui->text_setting);
}

/* bubble mode. */
void TalkWidget::on_bubble_font_toggled(bool checked)
{
    if(checked)
    {
        ui->bubble_font->setIcon(QIcon(":/res/talk/nnv.png"));
        F_M->m_customFontSelect->move(ui->bubble_font->mapToGlobal(QPoint(0,ui->bubble_font->height())));
        F_M->m_customFontSelect->show();
    }
    else
    {
        ui->bubble_font->setIcon(QIcon(":/res/talk/nnu.png"));
        F_M->m_customFontSelect->hide();
    }
}

void TalkWidget::on_bubble_font_size_toggled(bool checked)
{
    if(checked)
    {
        ui->bubble_font_size->setIcon(QIcon(":/res/talk/nnv.png"));
        F_M->m_bubbleFontSizeSelect->resize(ui->bubble_font_size->width(),150);
        F_M->m_bubbleFontSizeSelect->move(ui->bubble_font_size->mapToGlobal(QPoint(0,ui->bubble_font_size->height())));
        F_M->m_bubbleFontSizeSelect->show();
    }
    else
    {
        ui->bubble_font_size->setIcon(QIcon(":/res/talk/nnu.png"));
        F_M->m_bubbleFontSizeSelect->hide();
    }
}

void TalkWidget::on_sys_font_toggled(bool checked)
{
    if(checked)
    {
        ui->font_select->hide();
        ui->font_option->setVisible(true);
    }
}

void TalkWidget::on_color_font_toggled(bool checked)
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
void TalkWidget::on_font_option_toggled(bool checked)
{
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

void TalkWidget::on_font_select_toggled(bool checked)
{
    if(checked)
    {
        ui->font_select->setIcon(QIcon(":/res/talk/nnv.png"));
        F_M->m_sysFontSelect->resize(ui->font_select->width(),150);
        F_M->m_sysFontSelect->move(ui->font_select->mapToGlobal(QPoint(0,ui->font_select->height())));
        F_M->m_sysFontSelect->show();
    }
    else
    {
        ui->font_select->setIcon(QIcon(":/res/talk/nnu.png"));
        F_M->m_sysFontSelect->hide();
    }
}

void TalkWidget::on_font_size_toggled(bool checked)
{
    if(checked)
    {
        ui->font_size->setIcon(QIcon(":/res/talk/nnv.png"));
        F_M->m_textFontSizeSelect->resize(ui->font_size->width(),150);
        F_M->m_textFontSizeSelect->move(ui->font_size->mapToGlobal(QPoint(0,ui->font_size->height())));
        F_M->m_textFontSizeSelect->show();
    }
    else
    {
        ui->font_size->setIcon(QIcon(":/res/talk/nnu.png"));
        F_M->m_textFontSizeSelect->hide();
    }
}

void TalkWidget::on_bold_toggled(bool checked)
{
    ui->input;
}

void TalkWidget::on_italic_toggled(bool checked)
{
    ui->input->setFontItalic(checked);
}

void TalkWidget::on_underline_toggled(bool checked)
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

void TalkWidget::on_actionExpression_triggered(bool checked)
{
    E_M->history->hide();

    if(checked)
        E_M->expression->animationShow(E_M->history->size(),E_M->expression->size(),ui->tool->mapToGlobal(QPoint(0,0)));
    else
        E_M->expression->setVisible(false);
}

void TalkWidget::on_font_option_pressed()
{
    qDebug() << "font option" << ui->font_option->isChecked();
    if(!ui->font_option->isChecked())
    {
        ui->font_option->setChecked(true);
        ui->font_option->setIcon(QIcon(":/res/talk/nnv.png"));
        F_M->m_customFontSelect->resize(ui->font_option->width(),150);
        F_M->m_customFontSelect->move(ui->font_option->mapToGlobal(QPoint(0,ui->font_option->height())));
        F_M->m_customFontSelect->show();
    }
    else
    {
        ui->font_option->setChecked(true);
        ui->font_option->setIcon(QIcon(":/res/talk/nnu.png"));
        F_M->m_customFontSelect->hide();
    }
}

void TalkWidget::on_color_option_clicked()
{
    QTextCharFormat fmt = ui->input->currentCharFormat();
    QColor color = QColorDialog::getColor(fmt.foreground().color(),this,"Choose Color");
    fmt.setForeground(color);
    QTextCursor cursor = ui->input->textCursor();
    cursor.mergeCharFormat(fmt);
    ui->input->mergeCurrentCharFormat(fmt);
}
