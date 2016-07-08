#-------------------------------------------------
#
# Project created by QtCreator 2015-08-16T09:10:06
#
#-------------------------------------------------

QT       += core
QT       -= gui
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -O0
QMAKE_LFLAGS += -O0

TARGET = compiler
TEMPLATE = lib
CONFIG += staticlib

SOURCES += block.cpp \
    blocktype.cpp \
    flowchart.cpp \
    blockoption.cpp \
    blockpin.cpp \
    jsonforqt.cpp \
    overloadtype.cpp \
    compiledblockinfo.cpp \
    pintype.cpp \
    datatype.cpp \
    automatictypecast.cpp \
    c_exp.cpp \
    lisp_exp.cpp \
    c_stmt.cpp

HEADERS  += block.h \
    blocktype.h \
    flowchart.h \
    blockoption.h \
    blockpin.h \
    jsonforqt.h \
    overloadtype.h \
    compiledblockinfo.h \
    pintype.h \
    datatype.h \
    automatictypecast.h \
    overloadresult.h \
    c_exp.h \
    lisp_exp.h \
    c_stmt.h

#QMAKE_POST_LINK += $$quote($$QMAKE_COPY) $$shell_quote($$shell_path($$OUT_PWD/debug/libcompiler.a)) $$shell_quote($$shell_path(..)) $$escape_expand(\\n\\t)
