#-------------------------------------------------
#
# Project created by QtCreator 2015-08-16T09:10:06
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = SignalCraft
TEMPLATE = app

CONFIG(debug, debug|release) {
    DESTDIR = debug
} else {
    DESTDIR = release
}

QMAKE_POST_LINK += $$quote($$QMAKE_COPY) $$shell_quote($$shell_path($$_PRO_FILE_PWD_/../blocks.json)) $$shell_quote($$shell_path($${OUT_PWD}/$$DESTDIR)) $$escape_expand(\\n\\t)

INCLUDEPATH += ../compiler
LIBS += -static -L$$shell_quote($$shell_path($$OUT_PWD/../compiler/$$DESTDIR)) -lcompiler

SOURCES += main.cpp\
    mainwindow.cpp \
    blockgraphicsitem.cpp \
    applicationdata.cpp \
    pingraphicsitem.cpp \
    wiregraphicsitem.cpp \
    blocktypelistmodel.cpp \
    flowchartgraphicsview.cpp \
    blockoptionsdialog.cpp \
    blockoptioncontrol.cpp \
    blockoptioncontrolinteger.cpp \
    blockoptioncontrolcombobox.cpp \

HEADERS  += mainwindow.h \
    blockgraphicsitem.h \
    applicationdata.h \
    pingraphicsitem.h \
    wiregraphicsitem.h \
    blocktypelistmodel.h \
    flowchartgraphicsview.h \
    blockoptionsdialog.h \
    blockoptioncontrol.h \
    blockoptioncontrolinteger.h \
    blockoptioncontrolcombobox.h \

FORMS    += mainwindow.ui \
    blockoptionsdialog.ui

RESOURCES += \
    resources.qrc


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

win32|macx {
    QMAKE_POST_LINK += $$quote($${QT_DEPLOY_COMMAND}) $${BUILD_TARGET} $$escape_expand(\\n\\t)
}
