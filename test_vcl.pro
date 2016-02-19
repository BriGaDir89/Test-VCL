#-------------------------------------------------
#
# Project created by QtCreator 2016-02-17T19:05:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_vcl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui

INCLUDEPATH += sdk\include
LIBS += -Lrelease -llibvlc


CONFIG += mobility
MOBILITY = 

