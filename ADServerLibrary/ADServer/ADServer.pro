#-------------------------------------------------
#
# Project created by QtCreator 2018-01-20T16:32:21
#
#-------------------------------------------------

QT       -= gui
QT      += core network sql

CONFIG += c++14

TARGET = ADServer
TEMPLATE = lib

DEFINES += AUTH

DEFINES += ADSERVER_LIBRARY

SOURCES += \
    common.cpp

HEADERS += \
    common.h \
    export.h

include(core/core.pri)
include(controllers/controllers.pri)
include(guards/guards.pri)
include(sessions/sessions.pri)
include(tasks/tasks.pri)
include(middlewares/middlewares.pri)
include(network/network.pri)

unix:!macx|win32: LIBS += -L$$OUT_PWD/../3rdParty/qhttp/xbin/ -lqhttp

INCLUDEPATH += $$PWD/../3rdParty/qhttp/src
DEPENDPATH += $$PWD/../3rdParty/qhttp/src
