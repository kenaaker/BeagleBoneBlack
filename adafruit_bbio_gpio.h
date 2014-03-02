#ifndef ADAFRUIT_BBIO_GPIO_H
#define ADAFRUIT_BBIO_GPIO_H

#include <QDir>
#include <QFile>
#include <list>

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
    Adafruit_bbio_gpio(const string &in_gpio_key);
    ~Adafruit_bbio_gpio(void);
    int gpio_set_direction(const string &direction);
    string gpio_get_direction();
    int gpio_set_value(const string &value);
    string gpio_get_value();

private:
    int gpio_export(const string &in_gpio_key);
    int gpio_number;            /* The GPIO pin number */
    string gpio_key;            /* Key string for the pin */
    QDir gpio_directory;        /* Directory controlling this GPIO */
    string io_direction;        /* "out" or "in" */
};
extern pins_table pin_lookup;

#endif // ADAFRUIT_BBIO_GPIO_H
