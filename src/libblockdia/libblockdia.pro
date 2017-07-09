#-------------------------------------------------
#
# Project created by QtCreator 2017-03-19T12:28:12
#
#-------------------------------------------------

VERSION = "0.1devel"

QT       += widgets
QT       -= gui

CONFIG(debug, debug|release) {
    TARGET = libblockdia_d
}
CONFIG (release, debug|release) {
    TARGET = libblockdia
}

DESTDIR = ../../bin

TEMPLATE = lib

DEFINES += LIBBLOCKDIA_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH = ../../include/

SOURCES += libblockdia.cpp \
    block.cpp \
    graphicitemblock.cpp \
    viewblock.cpp \
    parameter.cpp \
    parameterint.cpp \
    input.cpp \
    output.cpp

HEADERS += ../../include/libblockdia.h\
    ../../include/block.h \
    ../../include/graphicitemblock.h \
    ../../include/viewblock.h \
    ../../include/parameter.h \
    ../../include/parameterint.h \
    ../../include/input.h \
    ../../include/output.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
