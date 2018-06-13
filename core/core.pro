QT       += core network

TARGET = Core
TEMPLATE = lib

DEFINES += \
    WM_CORE_LIBRARY \
    WM_LIBRARY \
    WMP_LIBRARY \
    WMP_QT \
    LTM_DESC \
    USE_LTM

include(../global/global.pri)
include(weatherservice/weatherservice.pri)
include(skinservice/skinservice.pri)
include(clientservice/clientservice.pri)
include(abstractservice/abstractservice.pri)
include(wmcore/wmcore.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../wmp/release/ -lwmp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../wmp/debug/ -lwmp
else:unix: LIBS += -L$$OUT_PWD/../wmp/ -lwmp

INCLUDEPATH += $$PWD/../wmp
DEPENDPATH += $$PWD/../wmp
