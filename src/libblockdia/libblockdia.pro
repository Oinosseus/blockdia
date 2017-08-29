TEMPLATE = lib

# VERSION = Major . Minor . Patch
VERSION = 0.0.0

# defining Qt modules
QT += widgets
QT += gui

# specify the target filename
# for debug version a "_d" is appended
CONFIG(debug, debug|release) {
    TARGET = libblockdia_d
} else {
    TARGET = libblockdia
}

# define output directories
DESTDIR = $$PWD/../../bin
CONFIG(debug, debug|release) {
    MOC_DIR     = $$PWD/../../build/$${TARGET}_debug/
    OBJECTS_DIR = $$PWD/../../build/$${TARGET}_debug/
    RCC_DIR     = $$PWD/../../build/$${TARGET}_debug/
    UI_DIR      = $$PWD/../../build/$${TARGET}_debug/
}
CONFIG(release, debug|release) {
    MOC_DIR     = $$PWD/../../build/$${TARGET}_release/
    OBJECTS_DIR = $$PWD/../../build/$${TARGET}_release/
    RCC_DIR     = $$PWD/../../build/$${TARGET}_release/
    UI_DIR      = $$PWD/../../build/$${TARGET}_release/
}


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

# the header files are put into separate directory
# for easier deployment of the library
INCLUDEPATH += ../../include/

SOURCES +=  \
            block.cpp \
            graphicitemblock.cpp \
            viewblock.cpp \
            viewblockeditor.cpp \
            graphicitemblockheader.cpp \
            graphicitemtextbox.cpp \
            graphicitemparameter.cpp \
            graphiciteminput.cpp \
            graphicitemoutput.cpp \
            dialogeditheader.cpp \
            dialogeditinput.cpp \
            dialogeditoutput.cpp \
            dialogeditparameterint.cpp \
            dialogeditparameterstr.cpp \
            dialogeditparameterenum.cpp \
    blockinput.cpp \
    blockoutput.cpp \
    blockparameter.cpp \
    blockparameterenum.cpp \
    blockparameterint.cpp \
    blockparameterstr.cpp

HEADERS +=  ../../include/libglobals.h \
            ../../include/libblockdia.h \
            ../../include/block.h \
            ../../include/graphicitemblock.h \
            ../../include/viewblock.h \
            ../../include/viewblockeditor.h \
            ../../include/graphicitemblockheader.h \
            ../../include/graphicitemtextbox.h \            
            ../../include/graphicitemparameter.h \
            ../../include/graphiciteminput.h \
            ../../include/graphicitemoutput.h \
            ../../include/dialogeditheader.h \
            ../../include/dialogeditinput.h \
            ../../include/dialogeditoutput.h \
            ../../include/dialogeditparameterint.h \
            ../../include/dialogeditparameterenum.h \
            ../../include/dialogeditparameterstr.h \
    ../../include/blockinput.h \
    ../../include/blockoutput.h \
    ../../include/blockparameter.h \
    ../../include/blockparameterenum.h \
    ../../include/blockparameterint.h \
    ../../include/blockparameterstr.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
