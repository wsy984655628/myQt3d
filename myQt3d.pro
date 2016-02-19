#-------------------------------------------------
#
# Project created by QtCreator 2016-01-06T16:03:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += 3dcore 3drenderer 3dinput 3dquick

TARGET = myQt3d
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    Assets.qrc \
    qml.qrc
