
#include <QtCore>
#include <QString>

#include <motor.h>
#include "adafruit_bbio_pwm.h"

motor::motor() {
    pwm_pin = "Uninit";
    dir_pin = "Uninit";
}

motor::~motor() {
    delete dc;
    delete dir;
}

/* Create the control structure to setup, run, and shutdown a motor  */
/* Attached to a GPIO pin */
motor::motor(e_motor_id m_id) {
    switch (m_id) {
        case e_motor_id::e_motor_a:
            pwm_pin = motor_a_pwm_pin;
            dir_pin = motor_a_dir_pin;
            break;
        case e_motor_id::e_motor_b:
            pwm_pin = motor_b_pwm_pin;
            dir_pin = motor_b_dir_pin;
            break;
        case e_motor_id::e_motor_c:
            pwm_pin = motor_c_pwm_pin;
            dir_pin = motor_c_dir_pin;
            break;
        case e_motor_id::e_motor_d:
            pwm_pin = motor_d_pwm_pin;
            dir_pin = motor_d_dir_pin;
            break;
        default:
            abort();
            break;
    } /* endswitch */
    motor_id = m_id;
    motor_speed = 0;
    dir = new Adafruit_bbio_gpio(dir_pin.toStdString());
    dir->gpio_set_direction("out");
    dir->gpio_set_value("1");
    dc = new Adafruit_bbio_pwm(pwm_pin.toStdString());
}

void motor::motor_run(int8_t speed) {
    uint8_t direction = (speed > 0);
    uint8_t abs_speed = abs(speed);

    if (direction) {
        dir->gpio_set_value("0");
    } else {
        dir->gpio_set_value("1");
    } /* endif */
    dc->set_duty_cycle(abs_speed);
}

void motor::motor_stop(void) {
    motor_run(0);
}
