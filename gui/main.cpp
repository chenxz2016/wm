#include "loginwindow.h"
#include "mainwindow.h"
#include "contacttalk.h"
#include "wmtrayicon.h"
#include "application.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);

    WMApplication app;
    app.init();

    WMTrayIcon ti;
    ti.init();
    ti.show();

    return a.exec();
}
