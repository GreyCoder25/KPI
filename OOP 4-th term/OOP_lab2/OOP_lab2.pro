#-------------------------------------------------
#
# Project created by QtCreator 2016-04-04T20:18:00
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = OOP_lab2
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    Test.cpp \
    Database.cpp \
    Employee.cpp \
    Manager.cpp

HEADERS += \
    Employee.h \
    Manager.h \
    Database.h

OTHER_FILES += \
    input.csv
