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
    rgbcontroller.cpp \
    ambilight.cpp \
    tabcontent.cpp \
    screenregion.cpp \
    renderarea.cpp \
    lightmusic.cpp

HEADERS  += mainwindow.h \
    rgbcontroller.h \
    ambilight.h \
    tabcontent.h \
    screenregion.h \
    renderarea.h \
    lightmusic.h

FORMS    += mainwindow.ui \
    rgbcontroller.ui \
    ambilight.ui \
    lightmusic.ui
