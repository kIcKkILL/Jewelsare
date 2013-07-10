#-------------------------------------------------
#
# Project created by QtCreator 2013-07-09T22:41:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Jewelsare
TEMPLATE = app
CONFIG += c++11


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/gamestate.cpp \
    src/board.cpp \
    src/game.cpp \
    src/gamelogic.cpp \
    src/jewel.cpp \
    src/scoresystem.cpp \
    src/util/jewelbutton.cpp

HEADERS  += src/mainwindow.h \
    src/gamestate.h \
    src/board.h \
    src/game.h \
    src/gamelogic.h \
    src/jewel.h \
    src/scoresystem.h \
    src/util/jewelbutton.h

FORMS    += src/mainwindow.ui

OTHER_FILES +=
