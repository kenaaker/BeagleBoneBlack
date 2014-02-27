#ifndef ADAFRUIT_BBIO_PWM_H
#define ADAFRUIT_BBIO_PWM_H

#include "adafruit_bbio_pwm_global.h"

using namespace std;

class pins_table {
public:
    pins_table();
    ~pins_table();
    int gpio_by_key(const string &key);
    int gpio_by_name(const string &name);
    int ain_by_key(const string &key);
    int ain_by_name(const string &name);
    string pwm_key_by_key(const string &key);
    string pwm_key_by_name(const string &name);
    int gpio_number(const string &key);
    int adc_ain_number(const string &n);

private:
    typedef struct pins_entry {
        string name;
        string key;
        int16_t gpio;
        int16_t pwm_mux_mode;
        int16_t ain;
    } pins_entry_t;
    list<pins_entry_t> pins;
};

class ADAFRUIT_BBIO_PWMSHARED_EXPORT Adafruit_bbio_pwm {

public:
    Adafruit_bbio_pwm();
    ~Adafruit_bbio_pwm();
private:
    string build_path(const string &partial_path, const string &prefix);
    int load_device_tree(const string &tree_add_name);
    int unload_device_tree(const string &tree_del_name);

};

#endif // ADAFRUIT_BBIO_PWM_H
