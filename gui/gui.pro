#-------------------------------------------------
#
# Project created by QtCreator 2017-11-01T21:33:28
#
#-------------------------------------------------

QT       += core gui quickwidgets quick qml multimedia multimediawidgets

unix: QT += x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app

include(mv/mv.pri)
include(contacts/contacts.pri)
include(expression/expression.pri)
include(sessions/sessions.pri)
include(groups/groups.pri)
include(photoview/photoview.pri)
include(add/add.pri)
include(files/files.pri)
include(brief/brief.pri)
include(font/font.pri)
include(talk/talk.pri)
include(trayicon/trayicon.pri)
include(verify/verify.pri)
include(util/util.pri)
include(login/login.pri)
include(mainwindow/mainwindow.pri)
include(setting/setting.pri)
include(enshrine/enshrine.pri)
include(repost/repost.pri)
include(warning/warning.pri)
include(window/window.pri)
include(skin/skin.pri)
include(weather/weather.pri)
include(menu/menu.pri)
include(qss/qss.pri)
include(app/app.pri)
include(telephone/telephone.pri)
include(../global/global.pri)

SOURCES += main.cpp

RESOURCES += \
    res.qrc

#DEFINES += \
DEFINES += \
    WMP_QT

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../animation/release/ -lAnimation
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../animation/debug/ -lAnimation
else:unix: LIBS += -L$$OUT_PWD/../animation/ -lAnimation

INCLUDEPATH += $$PWD/../animation
DEPENDPATH += $$PWD/../animation


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../core/ -lCore

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../media/release/ -lMedia
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../media/debug/ -lMedia
else:unix: LIBS += -L$$OUT_PWD/../media/ -lMedia

INCLUDEPATH += $$PWD/../media
DEPENDPATH += $$PWD/../media

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../bubble/release/ -lBubble
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../bubble/debug/ -lBubble
else:unix: LIBS += -L$$OUT_PWD/../bubble/ -lBubble

INCLUDEPATH += $$PWD/../bubble
DEPENDPATH += $$PWD/../bubble

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../additional/release/ -lAdditional
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../additional/debug/ -lAdditional
else:unix: LIBS += -L$$OUT_PWD/../additional/ -lAdditional

INCLUDEPATH += $$PWD/../additional
DEPENDPATH += $$PWD/../additional


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../wmp/release/ -lwmp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../wmp/debug/ -lwmp
else:unix: LIBS += -L$$OUT_PWD/../wmp/ -lwmp

INCLUDEPATH += $$PWD/../wmp
DEPENDPATH += $$PWD/../wmp
