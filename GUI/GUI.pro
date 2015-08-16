#-------------------------------------------------
#
# Project created by QtCreator 2015-08-16T09:10:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    block.cpp \
    mygraphicsview.cpp

HEADERS  += mainwindow.h \
    block.h \
    mygraphicsview.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
