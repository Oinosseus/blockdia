TEMPLATE = app
QT      += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# define output directories0
DESTDIR = $$PWD/../../bin
CONFIG(debug, debug|release) {
    MOC_DIR     = $$PWD/../../build/$${TARGET}_debug/
    OBJECTS_DIR = $$PWD/../../build/$${TARGET}_debug/
    RCC_DIR     = $$PWD/../../build/$${TARGET}_debug/
    UI_DIR      = $$PWD/../../build/$${TARGET}_debug/
} else {
    MOC_DIR     = $$PWD/../../build/$${TARGET}_release/
    OBJECTS_DIR = $$PWD/../../build/$${TARGET}_release/
    RCC_DIR     = $$PWD/../../build/$${TARGET}_release/
    UI_DIR      = $$PWD/../../build/$${TARGET}_release/
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=  main.cpp \
            mainwindow.cpp

HEADERS +=  mainwindow.h


# include library
CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../bin/ -llibblockdia_d
} else {
    LIBS += -L$$PWD/../../bin/ -llibblockdia
}
INCLUDEPATH += ../../include/
DEPENDPATH += $$PWD/../../build
