#-------------------------------------------------
#
# Project created by QtCreator 2015-08-16T09:10:06
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = unnamedsoftware
TEMPLATE = app

SOURCES += gui/main.cpp\
    gui/mainwindow.cpp \
    gui/blockgraphicsitem.cpp \
    flowchart/block.cpp \
    flowchart/blocktype.cpp \
    flowchart/flowchart.cpp \
    jsoncpp.cpp \
    usb/deviceconnection.cpp \
    compiler/compiler.cpp \
    blocktypesreader.cpp \
    gui/applicationdata.cpp \
    gui/pingraphicsitem.cpp \
    flowchart/flowchartserializer.cpp \
    gui/wiregraphicsitem.cpp \
    gui/blocktypelistmodel.cpp \
    gui/flowchartgraphicsview.cpp \
    gui/blockoptionsdialog.cpp \
    gui/blockoptioncontrol.cpp \
    gui/blockoptioncontrolinteger.cpp \
    flowchart/blockoption.cpp \
    flowchart/blockoptioninteger.cpp \
    flowchart/blockoptioncombobox.cpp \
    gui/blockoptioncontrolcombobox.cpp

HEADERS  += gui/mainwindow.h \
    gui/blockgraphicsitem.h \
    flowchart/block.h \
    flowchart/blocktype.h \
    flowchart/flowchart.h \
    usb/deviceconnection.h \
    compiler/compiler.h \
    blocktypesreader.h \
    gui/applicationdata.h \
    flowchart/datatype.h \
    gui/pingraphicsitem.h \
    flowchart/flowchartserializer.h \
    gui/wiregraphicsitem.h \
    gui/blocktypelistmodel.h \
    gui/flowchartgraphicsview.h \
    gui/blockoptionsdialog.h \
    gui/blockoptioncontrol.h \
    gui/blockoptioncontrolinteger.h \
    flowchart/blockoption.h \
    flowchart/blockoptioninteger.h \
    flowchart/blockoptioncombobox.h \
    gui/blockoptioncontrolcombobox.h

FORMS    += gui/mainwindow.ui \
    gui/blockoptionsdialog.ui

RESOURCES += \
    gui/resources.qrc

# include libUSB
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


CONFIG(debug, debug|release) {
    DESTDIR = debug
} else {
    DESTDIR = release
}
OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.rcc
UI_DIR = $$DESTDIR/.ui

#deployment to build folder
isEmpty(TARGET_EXT) {
    win32 {
        TARGET_CUSTOM_EXT = .exe
    }
    macx {
        TARGET_CUSTOM_EXT = .app
    }
} else {
    TARGET_CUSTOM_EXT = $${TARGET_EXT}
}

win32 {
    QT_DEPLOY_COMMAND = windeployqt
}
macx {
    QT_DEPLOY_COMMAND = macdeployqt
}

BUILD_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/$$DESTDIR/$${TARGET}$${TARGET_CUSTOM_EXT}))

QMAKE_POST_LINK += $$quote($${QT_DEPLOY_COMMAND}) $$quote($${BUILD_TARGET}) $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $$quote($$QMAKE_COPY) $$quote($$shell_path($$_PRO_FILE_PWD_/blocks.json)) $$quote($$shell_path($${OUT_PWD}/$$DESTDIR)) $$escape_expand(\\n\\t)




