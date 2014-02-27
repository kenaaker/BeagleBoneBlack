#-------------------------------------------------
#
# Project created by QtCreator 2014-02-22T10:45:50
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bbb_motor_control

TEMPLATE = app

SOURCES += main.cpp\
    motor_control.cpp \
    motor.cpp \
    adafruit_bbio_pwm.cpp

HEADERS  += motor_control.h \
    motor.h \
    adafruit_bbio_pwm.h \
    adafruit_bbio_pwm_global.h

FORMS    += motor_control.ui

target.path += /home/kdaaker/test_code
INSTALLS += target
