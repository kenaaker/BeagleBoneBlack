#include <QFile>

#include "adafruit_bbio_gpio.h"

Adafruit_bbio_gpio::Adafruit_bbio_gpio() {
    gpio = 9999;
    gpio_key = "uninit";
    gpio_directory = "";
    io_direction = true;
}

Adafruit_bbio_gpio::Adafruit_bbio_gpio(const string &gpio_key) {

}
