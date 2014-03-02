#ifndef ADAFRUIT_BBIO_GPIO_H
#define ADAFRUIT_BBIO_GPIO_H

#include <QDir>
#include <QFile>
#include "adafruit_bbio_pwm.h"

using namespace std;

#include <string>
#include <list>
#include <initializer_list>
#include <algorithm>

static const string io_output = "out";
static const string io_input = "in";

class Adafruit_bbio_gpio {

public:

    Adafruit_bbio_gpio();
    Adafruit_bbio_gpio(const string &gpio_key);

private:

    unsigned int gpio;          /* The GPIO pin number */
    string gpio_key;            /* Key string for the pin */
    QDir gpio_directory;        /* Directory controlling this GPIO */
    string io_direction;        /* "out" or "in" */
};
extern pins_table pin_lookup;

#endif // ADAFRUIT_BBIO_GPIO_H
