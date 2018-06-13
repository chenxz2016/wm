#include "qssloader.h"

#include <QFile>
#include <QWidget>


QssLoader *QssLoader::loader = 0;


void QssLoader::setTheme(const QString &theme)
{
    if(!loader)
        QssLoader::loader = new QssLoader;

    loader->theme = theme;
    QList<QWidget *> list = loader->map.keys();
    foreach(QWidget *widget,list)
        load(widget,loader->map[widget]);
}

void QssLoader::load(QWidget *widget,const QString &file)
{
    if(!loader)
        QssLoader::loader = new QssLoader;

    QFile f(loader->themePath()+"/"+file+".qss");
    if(f.open(QIODevice::ReadOnly))
    {
        widget->setStyleSheet(QString(f.readAll()));
        loader->appendWidget(widget,file);
    }
}

QString QssLoader::themePath()
{
    return theme;
}

QssLoader::QssLoader()
{
    theme = ":/res/qss";
}

void QssLoader::appendWidget(QWidget *widget, const QString &file)
{
    map[widget] = file;
}

void QssLoader::resetWidget()
{

}
