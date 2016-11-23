#-------------------------------------------------
#
# Project created by QtCreator 2015-05-17T22:51:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mynotepad
TEMPLATE = app


SOURCES += main.cpp\
        notepad.cpp \
    about.cpp

HEADERS  += notepad.h \
    about.h

FORMS    += notepad.ui \
    about.ui

RESOURCES += \
    icon.qrc

RC_ICONS = myappico.ico

RC_FILE = myapp.rc