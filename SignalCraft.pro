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

SOURCES += gui/main.cpp\
    gui/mainwindow.cpp \
    gui/blockgraphicsitem.cpp \
    flowchart/block.cpp \
    flowchart/blocktype.cpp \
    flowchart/flowchart.cpp \
    gui/applicationdata.cpp \
    gui/pingraphicsitem.cpp \
    gui/wiregraphicsitem.cpp \
    gui/blocktypelistmodel.cpp \
    gui/flowchartgraphicsview.cpp \
    gui/blockoptionsdialog.cpp \
    gui/blockoptioncontrol.cpp \
    gui/blockoptioncontrolinteger.cpp \
    flowchart/blockoption.cpp \
    flowchart/blockoptioninteger.cpp \
    flowchart/blockoptioncombobox.cpp \
    gui/blockoptioncontrolcombobox.cpp \
    flowchart/blockpin.cpp \
    jsonforqt.cpp \
    flowchart/overloadtype.cpp \
    compiler/compiledblockinfo.cpp \
    flowchart/pintype.cpp \
    compiler/datatype.cpp \
    compiler/automatictypecast.cpp \
    compiler/compiler.cpp \
    compiler/c_exp.cpp \
    compiler/lisp_exp.cpp \
    compiler/c_stmt.cpp

HEADERS  += gui/mainwindow.h \
    gui/blockgraphicsitem.h \
    flowchart/block.h \
    flowchart/blocktype.h \
    flowchart/flowchart.h \
    gui/applicationdata.h \
    gui/pingraphicsitem.h \
    gui/wiregraphicsitem.h \
    gui/blocktypelistmodel.h \
    gui/flowchartgraphicsview.h \
    gui/blockoptionsdialog.h \
    gui/blockoptioncontrol.h \
    gui/blockoptioncontrolinteger.h \
    flowchart/blockoption.h \
    flowchart/blockoptioninteger.h \
    flowchart/blockoptioncombobox.h \
    gui/blockoptioncontrolcombobox.h \
    flowchart/blockpin.h \
    jsonforqt.h \
    flowchart/overloadtype.h \
    compiler/compiledblockinfo.h \
    flowchart/pintype.h \
    compiler/datatype.h \
    compiler/automatictypecast.h \
    compiler/overloadresult.h \
    compiler/compiler.h \
    compiler/c_exp.h \
    compiler/lisp_exp.h \
    compiler/c_stmt.h

FORMS    += gui/mainwindow.ui \
    gui/blockoptionsdialog.ui

RESOURCES += \
    gui/resources.qrc

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

win32|macx {
    QMAKE_POST_LINK += $$quote($${QT_DEPLOY_COMMAND}) $${BUILD_TARGET} $$escape_expand(\\n\\t)
}

QMAKE_POST_LINK += $$quote($$QMAKE_COPY) $$shell_quote($$shell_path($$_PRO_FILE_PWD_/blocks.json)) $$shell_quote($$shell_path($${OUT_PWD}/$$DESTDIR)) $$escape_expand(\\n\\t)
