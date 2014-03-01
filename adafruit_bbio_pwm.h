#ifndef ADAFRUIT_BBIO_PWM_H
#define ADAFRUIT_BBIO_PWM_H

#include "adafruit_bbio_pwm_global.h"
#include <QFile>

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

enum class motor_dirs {
    md_cw,              /* Motor direction clockwise */
    md_ccw              /* Motor direction counter clockwise ... aka widdershins */
};

class ADAFRUIT_BBIO_PWMSHARED_EXPORT Adafruit_bbio_pwm {

public:
    Adafruit_bbio_pwm();
    Adafruit_bbio_pwm(const string &key);
    ~Adafruit_bbio_pwm();
    void set_frequency(float in_freq);
    void set_duty_cycle(float in_duty);
    void set_polarity(bool in_polarity);
    float get_frequency(void);
    float get_duty_cycle(void);
    bool get_polarity(void);
private:
    string build_path(const string &partial_path, const string &prefix);
    int load_device_tree(const string &tree_add_name);
    int unload_device_tree(const string &tree_del_name);
    string pwm_name;
    string ocp_dir;
    string period_file_name;
    string duty_file_name;
    string polarity_file_name;
    QFile period_file;
    QFile duty_file;
    QFile polarity_file;
    float freq;
    float duty_cycle_percent;
    bool polarity;
};

#endif // ADAFRUIT_BBIO_PWM_H
