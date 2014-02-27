#ifndef ADAFRUIT_BBIO_PWM_GLOBAL_H
#define ADAFRUIT_BBIO_PWM_GLOBAL_H

#include <string>
#include <list>
#include <initializer_list>
#include <algorithm>

#include <QtCore/qglobal.h>

#if defined(ADAFRUIT_BBIO_PWM_LIBRARY)
#  define ADAFRUIT_BBIO_PWMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ADAFRUIT_BBIO_PWMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ADAFRUIT_BBIO_PWM_GLOBAL_H
