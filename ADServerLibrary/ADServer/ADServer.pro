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
    session.cpp \
    registers.cpp \
    filecontroller.cpp \
    authengine.cpp \
    authcontroller.cpp \
    adnconnection.cpp \
    defs.cpp \
    adntaskmanager.cpp \
    adserver_p.cpp \
    adserver.cpp

HEADERS += \
    session.h \
    registers.h \
    filecontroller.h \
    authengine.h \
    authcontroller.h \
    adncontroller.h \
    defs.h \
    adntaskmanager.h \
    export.h \
    adserver_p.h \
    adserver.h

unix {
    HEADERS += deathhandler.h
    SOURCES += deathhandler.cpp

    LIBS += -ldl

    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdParty/qhttp/src/release/ -lqhttp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdParty/qhttp/src/debug/ -lqhttp
else:unix: LIBS += -L$$OUT_PWD/../3rdParty/qhttp/src/ -lqhttp

INCLUDEPATH += $$PWD/../3rdParty/qhttp/src
DEPENDPATH += $$PWD/../3rdParty/qhttp/src
