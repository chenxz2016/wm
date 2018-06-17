QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Media
TEMPLATE = lib

include(video/video.pri)
include(audio/audio.pri)
include(../global/global.pri)

DEFINES += \
    WM_MEDIA_LIBRARY \
    WM_LIBRARY
