#ifndef TALKWIDGET_H
#define TALKWIDGET_H

#include <QListWidget>
#include <QWidget>

namespace Ui
{
class TalkWindow;
class TalkWindowWarnTip;
class BubbleFontSelect;
}

class TalkWindowWarnTip : public QWidget
{
    Q_OBJECT
public:
    TalkWindowWarnTip(QWidget *parent);
    ~TalkWindowWarnTip();

    void setWarnText(const QString &text);
    QString warnText()const;

    void pop(const QSize &size,const QString &warning = "");
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::TalkWindowWarnTip *ui;
    QTimer *timer;
};

class TextOptionSelect : public QListWidget
{
    Q_OBJECT
public:
    explicit TextOptionSelect(QWidget *parent = 0);
    void show();
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void focusOutEvent(QFocusEvent *event);
signals:
    void select(QString);
    void aboutToHide();
private slots:
    void clickedSlot(QListWidgetItem *item);
};

class BubbleFontSelect : public QWidget
{
    Q_OBJECT
public:
    BubbleFontSelect(QWidget *parent = 0);
    ~BubbleFontSelect();

signals:
    void selectFont(QFont);
private:
    Ui::BubbleFontSelect *ui;
};

class ExpressionHistory;
class ExpressionWidget;

class TalkWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TalkWindow(QWidget *parent = 0);
    ~TalkWindow();

    void showWarning(const QString &warning);
public slots:
    void insertPixmap(QPixmap);
    void setFontSize(QString);
    void setFont(QString);

    void expressionReset();
    void sysFontReset();
    void customFontReset();
    void textFontSizeReset();
    void bubbleFontSizeReset();
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void focusInEvent(QFocusEvent *event);
    void showEvent(QShowEvent *event);
private:
    void startRecordVoice();
    void cancelRecordVoice();
    void endRecordVoice();
    void sendVoice();
private slots:
    void recordingVoice();
private slots:
    void on_radioButton_2_toggled(bool checked);

    void selectLocalPicture();
    void on_actionFont_toggled(bool arg1);

    void on_actionVoice_triggered();
    void on_voice_send_clicked();

    void on_voice_cancel_clicked();
    void on_actionExpression_hovered();

    void on_actionExpression_toggled(bool arg1);

    void on_bubble_toggled(bool checked);

    void on_text_toggled(bool checked);

    void on_bubble_font_toggled(bool checked);

    void on_bubble_font_size_toggled(bool checked);

    void on_sys_font_toggled(bool checked);

    void on_color_font_toggled(bool checked);

    void on_font_option_toggled(bool checked);

    void on_font_select_toggled(bool checked);

    void on_font_size_toggled(bool checked);

    void on_bold_toggled(bool checked);

    void on_italic_toggled(bool checked);

    void on_underline_toggled(bool checked);

    void on_actionExpression_triggered(bool checked);

    void on_font_option_pressed();

    void on_color_option_clicked();

    void on_log_toggled(bool checked);

    void on_right_tabCloseRequested(int index);

private:
    Ui::TalkWindow *ui;
    class TalkWindowPrivate *p_d;
    friend class TalkWindowPrivate;
};

#endif // TALKWIDGET_H
