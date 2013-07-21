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
QMAKE_CXXFLAGS += -std=c++11


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/gamestate.cpp \
    src/board.cpp \
    src/gamelogic.cpp \
    src/scoresystem.cpp \
    src/util/jewelbutton.cpp \
	src/util/jewelwidget.cpp \
    src/game.cpp \
    src/util/countdowntimer.cpp

HEADERS  += src/mainwindow.h \
    src/gamestate.h \
    src/board.h \
    src/gamelogic.h \
    src/util/jewelwidget.h \
    src/scoresystem.h \
    src/util/jewelbutton.h \
    src/game.h \
    src/util/countdowntimer.h

FORMS    += src/mainwindow.ui

OTHER_FILES +=
