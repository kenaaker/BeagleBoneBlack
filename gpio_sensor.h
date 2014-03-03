#ifndef GPIO_SENSOR_H
#define GPIO_SENSOR_H
#include "adafruit_bbio_adc.h"

using namespace std;

#include <string>

class gpio_sensor
{
public:
    gpio_sensor();
    gpio_sensor(const string in_lek_key, const string &in_adc_key);
    ~gpio_sensor();
    int sensor_read();
private:
    Adafruit_bbio_adc *sensor;
    Adafruit_bbio_gpio *led_control;
};

#endif // GPIO_SENSOR_H
