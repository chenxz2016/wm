#ifndef QSSLOADER_H
#define QSSLOADER_H

#include <QMap>
#include <QString>

class QWidget;

class QssLoader
{
public:
    static void setTheme(const QString &theme);
    static void load(QWidget *widget,const QString &file);

    QString themePath();
protected:
    QssLoader();
    void appendWidget(QWidget *widget,const QString &file);
    void resetWidget();
private:
    QMap<QWidget *,QString> map;
    QString theme;
    static QssLoader *loader;
};

#endif // QSSLOADER_H
