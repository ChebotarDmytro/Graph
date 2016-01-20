#-------------------------------------------------
#
# Project created by QtCreator 2015-07-02T16:49:36
#
#-------------------------------------------------

QT       += core gui
CONFIG += qwt

RESOURCES     = source.qrc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QWT_GRAF
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graf.cpp \
    panel.cpp

HEADERS  += mainwindow.h \
    graf.h \
    panel.h \
    settings.h


