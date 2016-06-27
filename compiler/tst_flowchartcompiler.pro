QT       += testlib
QT       -= gui

TARGET = tst_flowchartcompiler
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG(debug, debug|release) {
    DESTDIR = debug
} else {
    DESTDIR = release
}

INCLUDEPATH += ../compiler
LIBS += -static -L$$shell_quote($$shell_path($$OUT_PWD/../compiler/$$DESTDIR)) -lcompiler

SOURCES += tst_flowchartcompiler.cpp
