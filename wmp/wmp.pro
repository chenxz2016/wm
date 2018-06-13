#-------------------------------------------------
#
# Project created by QtCreator 2017-11-01T21:34:40
#
#-------------------------------------------------

QT       -= gui

TARGET = wmp
TEMPLATE = lib

DEFINES += \
    __cplusplus_ \
    WMP_LIBRARY \
    WMP_QT \
    LTM_DESC \
    USE_LTM \
    WIN32 \
    _DEBUG \
    _CRT_SECURE_NO_WARNINGS \
    _CRT_NONSTDC_NO_DEPRECATE \
    LTM_DESC \
    LTC_SOURCE \
    LTC_NO_TEST \
    LTC_NO_PROTOTYPES

QMAKE_LFLAGS_DEBUG = /DEBUG /NODEFAULTLIB:libc.lib /NODEFAULTLIB:libcmt.lib /NODEFAULTLIB:msvcrt.lib /NODEFAULTLIB:libcd.lib /NODEFAULTLIB:libcmtd.lib

SOURCES += \
    protocol_crypt.c \
    protocol_error.c \
    protocol_package.c \
    wm_protocol.c \
    wmp_beat_heart.c \
    wmp_file.c \
    wmp_group.c \
    wmp_login.c \
    wmp_message.c \
    wmp_register.c \
    wmp_session.c \
    wmp_sound.c \
    wmp_user.c \
    wmp_video.c \
    crc32.c

HEADERS += wm_protocol.h\
        wmp_global.h \
    protocol_package.h \
    wmp_beat_heart.h \
    wmp_file.h \
    wmp_group.h \
    wmp_login.h \
    wmp_message.h \
    wmp_register.h \
    wmp_session.h \
    wmp_sound.h \
    wmp_user.h \
    wmp_video.h \
    wmp_qt.h \
    protocol_crypt.h \
    protocol_def.h \
    crc32.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    README.txt


LIBS += -lAdvapi32

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libtomcrypt/lib/ -ltomcrypt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libtomcrypt/lib/ -ltomcryptd
else:unix: LIBS += -L$$PWD/libtomcrypt/lib/ -ltomcrypt

INCLUDEPATH += $$PWD/libtomcrypt/include
DEPENDPATH += $$PWD/libtomcrypt/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libtomcrypt/lib/libtomcrypt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libtomcrypt/lib/libtomcryptd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libtomcrypt/lib/tomcrypt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libtomcrypt/lib/tomcryptd.lib
else:unix: PRE_TARGETDEPS += $$PWD/libtomcrypt/lib/libtomcrypt.a


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libtomcrypt/lib/ -ltommath
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libtomcrypt/lib/ -ltommath
else:unix: LIBS += -L$$PWD/libtomcrypt/lib/ -ltommath

#INCLUDEPATH += $$PWD/libtomcrypt/include
#DEPENDPATH += $$PWD/libtomcrypt/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libtomcrypt/lib/libtommath.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libtomcrypt/lib/libtommath.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libtomcrypt/lib/tommath.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libtomcrypt/lib/tommath.lib
else:unix: PRE_TARGETDEPS += $$PWD/libtomcrypt/lib/libtommath.a
