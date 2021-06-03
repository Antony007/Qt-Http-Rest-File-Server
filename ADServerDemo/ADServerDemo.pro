QT += core network sql
QT -= gui

CONFIG += c++14

TARGET = ADNServerDemo
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    democontroller.cpp

HEADERS += \
    democontroller.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ADServerLibrary/ADServer/release/ -lADServer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ADServerLibrary/ADServer/debug/ -lADServer
else:unix: LIBS += -L$$OUT_PWD/../ADServerLibrary/ADServer/ -lADServer

INCLUDEPATH += $$PWD/../ADServerLibrary/ADServer
DEPENDPATH += $$PWD/../ADServerLibrary/ADServer

INCLUDEPATH += $$PWD/../ADServerLibrary/3rdParty/qhttp/src
DEPENDPATH += $$PWD/../ADServerLibrary/3rdParty/qhttp/src
