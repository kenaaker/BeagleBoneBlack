#include "gpio_sensor.h"
#include "adafruit_bbio_adc.h"
#include "adafruit_bbio_gpio.h"

gpio_sensor::gpio_sensor() {
    sensor = NULL;
}

gpio_sensor::gpio_sensor(const string in_led_key, const string &in_adc_key) {
    led_control = new Adafruit_bbio_gpio(in_led_key);
    led_control->gpio_set_direction("out");
    led_control->gpio_set_value("1");
    sensor = new Adafruit_bbio_adc(in_adc_key);
}

gpio_sensor::~gpio_sensor() {
    delete sensor;
}

int gpio_sensor::sensor_read() {
    return sensor->adc_read_value();
}
