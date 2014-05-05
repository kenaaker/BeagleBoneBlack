#include "gpio_sensor.h"
#include "adafruit_bbio_adc.h"
#include "adafruit_bbio_gpio.h"
#include <QtCore/qdebug.h>

gpio_sensor::gpio_sensor() {
    sensor = NULL;
}

gpio_sensor::gpio_sensor(const string in_led_key, const string &in_adc_key) {
    led_control = new Adafruit_bbio_gpio(in_led_key);
    led_control->gpio_set_direction("out");
    led_control->gpio_set_value("1");
    sensor = new Adafruit_bbio_adc(in_adc_key);
    low_bound = std::numeric_limits<unsigned int>::min();
    high_bound = std::numeric_limits<unsigned int>::max();
    in_bounds = true;
    read_interval = 0;
}

gpio_sensor::~gpio_sensor() {
    led_control->gpio_set_value("0");
    led_control->gpio_set_direction("in");
    delete led_control;
    delete sensor;
}

int gpio_sensor::sensor_read() {
    return sensor->adc_read_value();
}

void gpio_sensor::set_low_bound(int low) {
    low_bound = low;
} /* set_low_bound */

void gpio_sensor::set_high_bound(int high) {
    high_bound = high;
} /* set_high_bound */

void gpio_sensor::set_bounds(int low, int high) {
    low_bound = low;
    high_bound = high;
} /* set_bounds */

void gpio_sensor::set_in_or_out(bool in_out) {
    in_bounds = in_out;
} /* set_in_or_out */

int gpio_sensor::get_low_bound(void) {
    return low_bound;
} /* get_low_bound */

int gpio_sensor::get_high_bound(void) {
    return high_bound;
} /* get_high_bound */

void gpio_sensor::set_read_interval(int poll_interval_msec) {
    read_interval = poll_interval_msec;
    if (poll_interval_msec >= 0) {
        if (!read_timer.isActive()) {
            connect(&read_timer, SIGNAL(timeout()), this, SLOT(adc_read()));
        } /* endif */
        read_timer.start(read_interval);
    } else {
        if (read_timer.isActive()) {
            read_timer.stop();
        } /* endif */
    } /* endif */
} /* set_read_interval */

/* Timer driven function to sample ADC and emit signal if bounds call for it */
void gpio_sensor::adc_read(void) {
    int adc_reading = sensor_read();

//    qDebug() << "adc_reading = " << adc_reading;

    /* in_bounds means emit a signal if value is inside bounds */
    if (in_bounds) {
//        qDebug() << "in_bounds";
        if ((adc_reading > low_bound) && (adc_reading < high_bound)) {
            emit (adc_signal(adc_reading));
        } /* endif */
    } else { /* Otherwise, emit a signal if value is outside bounds */
//        qDebug() << "out_bounds";
        if ((adc_reading < low_bound) || (adc_reading > high_bound)) {
            emit (adc_signal(adc_reading));
        } /* endif */
    } /* endif */
} /* adc_read */
