#-------------------------------------------------
#
# Project created by QtCreator 2014-06-06T06:00:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = canvas
TEMPLATE = app


SOURCES += main.cpp\
    dialog.cpp \
    qshape.cpp \
    qautonode.cpp \
    lineobject.cpp \
    taskinfo.cpp \
    nodeparams.cpp \
    wfmaker.cpp

HEADERS  += \
    dialog.h \
    qshape.h \
    qautonode.h \
    lineobject.h \
    taskinfo.h \
    nodeparams.h \
    wfmaker.h

FORMS    += \
    dialog.ui
