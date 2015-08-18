#-------------------------------------------------
#
# Project created by QtCreator 2015-08-16T09:10:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UnnamedSoftware
TEMPLATE = app

SOURCES += gui/main.cpp\
    gui/mainwindow.cpp \
    gui/mygraphicsview.cpp \
    gui/myitemmodel.cpp \
    gui/blockgraphicsitem.cpp \
    flowchart/block.cpp \
    flowchart/blocktype.cpp \
    flowchart/flowchart.cpp \
    jsoncpp.cpp

HEADERS  += gui/mainwindow.h \
    gui/mygraphicsview.h \
    gui/myitemmodel.h \
    gui/blockgraphicsitem.h \
    flowchart/block.h \
    flowchart/blocktype.h \
    flowchart/flowchart.h \
    json/json.h \
    json/json-forwards.h

FORMS    += gui/mainwindow.ui

RESOURCES += \
    gui/resources.qrc
