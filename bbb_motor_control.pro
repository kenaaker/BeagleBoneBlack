#-------------------------------------------------
#
# Project created by QtCreator 2014-02-22T10:45:50
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += ../IOoo/include
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bbb_motor_control

TEMPLATE = app


SOURCES += main.cpp\
    motor_control.cpp \
    motor.cpp

HEADERS  += motor_control.h \
    motor.h

FORMS    += motor_control.ui

target.path += /home/kdaaker/test_code
INSTALLS += target

LIBS += -L$$PWD/../IOoo/lib/ -lgpiooo

INCLUDEPATH += $$PWD/../IOoo/include
DEPENDPATH += $$PWD/../IOoo/include

PRE_TARGETDEPS += $$PWD/../IOoo/lib/libgpiooo.a
