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
    jsoncpp.cpp \
    usb/deviceconnection.cpp

HEADERS  += gui/mainwindow.h \
    gui/mygraphicsview.h \
    gui/myitemmodel.h \
    gui/blockgraphicsitem.h \
    flowchart/block.h \
    flowchart/blocktype.h \
    flowchart/flowchart.h \
    json/json.h \
    json/json-forwards.h \
    usb/deviceconnection.h

FORMS    += gui/mainwindow.ui

RESOURCES += \
    gui/resources.qrc

win32 {
    INCLUDEPATH += $$(LIBUSBDIR)/libusb/
    !contains(QMAKE_TARGET.arch, x86_64) {
        #Win32
        LIBS += -L$$(LIBUSBDIR)/Win32/Release/lib/
    } else {
        #Win64
        LIBS += -L$$(LIBUSBDIR)/x64/Release/lib/
    }
    LIBS += -llibusb-1.0
}
linux-g++ {
    INCLUDEPATH += /usr/include/libusb-1.0/
    LIBS += -L/usr/lib/
    QMAKE_CXXFLAGS += -std=c++11
    LIBS += -lusb-1.0
}


