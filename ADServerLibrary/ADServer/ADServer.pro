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
    adconnection.cpp \
    adtaskmanager.cpp \
    session.cpp \
    registers.cpp \
    filecontroller.cpp \
    authengine.cpp \
    authcontroller.cpp \
    defs.cpp \
    adserver.cpp

HEADERS += \
    adcontroller.h \
    adtaskmanager.h \
    session.h \
    registers.h \
    filecontroller.h \
    authengine.h \
    authcontroller.h \
    defs.h \
    export.h \
    adserver.h

unix {
    HEADERS += $$PWD/../3rdParty/dh/deathhandler.h
    SOURCES += $$PWD/../3rdParty/dh/deathhandler.cc

    LIBS += -ldl

    target.path = /usr/lib
    INSTALLS += target
}



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdParty/qhttp/xbin/ -lqhttp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdParty/qhttp/xbin/ -lqhttp
else:unix:!macx: LIBS += -L$$OUT_PWD/../3rdParty/qhttp/src/ -lqhttp

INCLUDEPATH += $$PWD/../3rdParty/qhttp/src
DEPENDPATH += $$PWD/../3rdParty/qhttp/src
