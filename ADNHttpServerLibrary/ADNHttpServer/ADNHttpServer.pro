#-------------------------------------------------
#
# Project created by QtCreator 2018-01-20T16:32:21
#
#-------------------------------------------------

QT       -= gui
QT      += core network sql

CONFIG += c++14

TARGET = ADNHttpServer
TEMPLATE = lib

DEFINES += AUTH

DEFINES += ADNHTTPSERVER_LIBRARY

SOURCES += adnhttpserver.cpp \
    session.cpp \
    registers.cpp \
    filecontroller.cpp \
    deathhandler.cpp \
    authengine.cpp \
    authcontroller.cpp \
    adnconnection.cpp \
    defs.cpp \
    adntaskmanager.cpp

HEADERS += adnhttpserver.h \
    session.h \
    registers.h \
    filecontroller.h \
    deathhandler.h \
    authengine.h \
    authcontroller.h \
    adncontroller.h \
    defs.h \
    adntaskmanager.h \
    export.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../3rdParty/QHttp/release/ -lqhttp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../3rdParty/QHttp/debug/ -lqhttp
else:unix:!macx: LIBS += -L$$PWD/../3rdParty/QHttp/ -lqhttp

INCLUDEPATH += $$PWD/../3rdParty/QHttp
DEPENDPATH += $$PWD/../3rdParty/QHttp

LIBS += -ldl
