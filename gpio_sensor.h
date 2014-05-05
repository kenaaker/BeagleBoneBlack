#ifndef GPIO_SENSOR_H
#define GPIO_SENSOR_H
#include "adafruit_bbio_adc.h"

using namespace std;

#include <string>

class gpio_sensor : public QObject {
    Q_OBJECT
public:
    gpio_sensor();
    gpio_sensor(const string in_lek_key, const string &in_adc_key);
    ~gpio_sensor();
    int sensor_read();
    void set_low_bound(int low);
    void set_high_bound(int high);
    void set_bounds(int low, int high);
    void set_in_or_out(bool in_out);
    int get_low_bound(void);
    int get_high_bound(void);
    void set_read_interval(int poll_interval_msec);
signals:
    void adc_signal(int trigger_value);
private:
    Adafruit_bbio_adc *sensor;
    Adafruit_bbio_gpio *led_control;
    QTimer read_timer;
    unsigned read_interval;
    int low_bound;
    int high_bound;
    bool in_bounds;
private slots:
    void adc_read(void);
};

#endif // GPIO_SENSOR_H
