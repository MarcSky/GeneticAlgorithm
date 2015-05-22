#-------------------------------------------------
#
# Project created by QtCreator 2015-03-19T21:10:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = life2
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    standartwidget.cpp \
    geneticAlgorithm/chromosome.cpp \
    geneticAlgorithm/population.cpp

HEADERS  += mainwindow.h \
    standartwidget.h \
    geneticAlgorithm/chromosome.h \
    geneticAlgorithm/population.h

FORMS    += mainwindow.ui
