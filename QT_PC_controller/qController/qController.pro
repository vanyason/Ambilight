#-------------------------------------------------
#
# Project created by QtCreator 2018-06-06T13:00:11
#
#-------------------------------------------------

QT       += core gui multimedia serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qController
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mywidgets.cpp \
    tabcontents.cpp \
    audioinfo.cpp \
    lightmusicmode.cpp

HEADERS  += mainwindow.h \
    mywidgets.h \
    tabcontents.h \
    audioinfo.h \
    lightmusicmode.h

FORMS    += mainwindow.ui \
    rgbcontroller.ui \
    ambilight.ui \
    lightmusic.ui
