#ifndef SKINSETTING_H
#define SKINSETTING_H

#include <QWidget>

namespace Ui {
class SkinSetting;
}

class SkinSetting : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString error WRITE setError)
    Q_PROPERTY(QVariant serviceData WRITE setServiceData)
public:
    enum SettingOption
    {
        Skin,
        Show,
        ColoredBubble,
        UIManage
    };
    explicit SkinSetting(QWidget *parent = 0);
    ~SkinSetting();

    static SkinSetting *instance();
    static void openSettingOption(SettingOption option);

    void setError(const QString &error);
    void setServiceData(const QVariant &data);
protected:
    void setOption(SettingOption option);

    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_close_clicked();

    void on_right_clicked(const QModelIndex &index);

    void on_up_clicked();

    void on_down_clicked();

    void on_skin_clicked();

    void on_show_clicked();

    void on_bubble_clicked();

    void on_uimanage_clicked();

private:

    void updateUpDown();


    static SkinSetting *singletion;
    Ui::SkinSetting *ui;
    class SkinSettingPrivate *p_d;
    friend class SkinSettingPrivate;
};

#endif // SKINSETTING_H
