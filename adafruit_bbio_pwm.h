#ifndef ADAFRUIT_BBIO_PWM_H
#define ADAFRUIT_BBIO_PWM_H

#include <QFile>
#include "adafruit_bbio_util.h"

using namespace std;

enum class motor_dirs {
    md_cw,              /* Motor direction clockwise */
    md_ccw              /* Motor direction counter clockwise ... aka widdershins */
};

class Adafruit_bbio_pwm {

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
