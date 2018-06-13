QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Additional
TEMPLATE = lib

include(audioitem/audioitem.pri)
include(../global/global.pri)

DEFINES += \
    WM_ADDITIONAL_LIBRARY \
    WM_LIBRARY
