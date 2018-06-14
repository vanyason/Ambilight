#-------------------------------------------------
#
# Project created by QtCreator 2018-06-06T13:00:11
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qController
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rgbcontroller.cpp \
    ambilight.cpp \
    tabcontent.cpp \
    screenregion.cpp

HEADERS  += mainwindow.h \
    rgbcontroller.h \
    ambilight.h \
    tabcontent.h \
    screenregion.h

FORMS    += mainwindow.ui \
    rgbcontroller.ui \
    ambilight.ui
