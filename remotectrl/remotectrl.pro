QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoteCtrl
TEMPLATE = lib

include(hostctrl/hostctrl.pri)
include(../global/global.pri)

DEFINES += \
    WM_REMOTE_CTRL_LIBRARY \
    WM_LIBRARY
