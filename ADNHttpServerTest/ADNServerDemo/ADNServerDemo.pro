QT += core network sql
QT -= gui

CONFIG += c++14

TARGET = ADNServerDemo
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    democontroller.cpp

unix:!macx: LIBS += -L$$PWD/../../ADNHttpServerLibrary/build-ADNHttpServer-Desktop_Qt_5_5_1_GCC_64bit2-Debug/ -lADNHttpServer

INCLUDEPATH += $$PWD/../../ADNHttpServerLibrary/ADNHttpServer
DEPENDPATH += $$PWD/../../ADNHttpServerLibrary/ADNHttpServer

unix:!macx: LIBS += -L$$PWD/../../ADNHttpServerLibrary/3rdParty/QHttp/ -lqhttp

INCLUDEPATH += $$PWD/../../ADNHttpServerLibrary/3rdParty/QHttp
DEPENDPATH += $$PWD/../../ADNHttpServerLibrary/3rdParty/QHttp

HEADERS += \
    democontroller.h
