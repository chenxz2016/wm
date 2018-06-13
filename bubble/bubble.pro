QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bubble
TEMPLATE = lib

include(abstractbubble/abstractbubble.pri)
include(coloredbubble/coloredbubble.pri)
include(audiobubble/audiobubble.pri)
include(videobubble/videobubble.pri)
include(../global/global.pri)

DEFINES += \
    WM_BUBBLE_LIBRARY \
    WM_LIBRARY
