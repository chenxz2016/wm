QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Animation
TEMPLATE = lib

include(blink/blink.pri)
include(close/close.pri)
include(move/move.pri)
include(resize/resize.pri)
include(shock/shock.pri)
include(show/show.pri)
include(switch/switch.pri)
include(polygon/polygon.pri)
include(control/control.pri)
include(hide/hide.pri)
include(turn/turn.pri)
include(../global/global.pri)

DEFINES += \
    WM_ANIMATION_LIBRARY \
    WM_LIBRARY
