#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bulls-cows-qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    engine.cpp \
    newgame.cpp \
    rules.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    engine.h \
    newgame.h \
    rules.h \
    about.h

FORMS    += mainwindow.ui \
    newgame.ui \
    rules.ui \
    about.ui
