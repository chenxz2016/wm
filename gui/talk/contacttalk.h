#ifndef CONTACTTALK_H
#define CONTACTTALK_H

#include <QListWidget>
#include <QWidget>

namespace Ui{
class ContactTalk;
}

class AbstractMessageItem;

class ContactTalk : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int maxCount READ maxCount WRITE setMaxCount)
    Q_PROPERTY(QString chatter READ chatter WRITE setChatter)
    Q_PROPERTY(QList<QPixmap> photos READ photos WRITE setPhotos)
public:
    explicit ContactTalk(QWidget *parent = 0);
    ~ContactTalk();

    void appendItem(AbstractMessageItem *item);
    void appendItems(const QList<AbstractMessageItem *> &items);

    void prependItem(AbstractMessageItem *item);
    void prependItems(const QList<AbstractMessageItem *> &items);

    void removeItem(AbstractMessageItem *item);

    void setMaxCount(int count);
    int maxCount()const;

    void setChatter(const QString &chatter);
    QString chatter()const;

    void setPhotos(const QStringList &photos);
    void setPhotos(const QList<QPixmap> &photos);
    QList<QPixmap> photos();

    void showWarning(const QString &warning);

    void updateMessageItems();
signals:
    void headClicked(QString);
public slots:
    void send();

    void insertPixmap(QPixmap);
    void setFontSize(QString);
    void setFont(QString);

    void expressionReset();
    void sysFontReset();
    void customFontReset();
    void textFontSizeReset();
    void bubbleFontSizeReset();
protected:
    bool event(QEvent *event);
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
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
private:
    void startRecordVoice();
    void cancelRecordVoice();
    void endRecordVoice();
    void sendVoice();
private slots:
    void recordingVoice();
private slots:

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

//    void on_log_toggled(bool checked);

    void on_right_tabCloseRequested(int index);

    void on_actionEnterSend_triggered();

    void on_actionCEnterSend_triggered();

    void on_send_menu_clicked();

    void on_record_menu_clicked();

    void on_ctrl_toggled(bool checked);

private:
    Ui::ContactTalk *ui;
    class ContactTalkPrivate *p_d;
    friend class ContactTalkPrivate;
};

#endif // CONTACTTALK_H
