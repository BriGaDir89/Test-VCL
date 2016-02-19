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
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += H:\OneDrive\GitHub\vlc-2.2.2_debug\sdk\include
INCLUDEPATH += H:\OneDrive\GitHub\vlc-2.2.2_debug\sdk\include\vlc\plugins
LIBS += -LH:\OneDrive\GitHub\vlc-2.2.2_debug -llibvlc

#LIBS += -LH:\OneDrive\GitHub\vlc-2.2.1 -llibvlccore
#LIBS += -LH:\OneDrive\GitHub\vlc-2.2.1 -laxvlc
#LIBS += -LH:\OneDrive\GitHub\vlc-2.2.1 -lnpvlc

CONFIG += mobility
MOBILITY = 

