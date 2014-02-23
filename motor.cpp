
#include <QtCore>
#include <QString>

#include <motor.h>

motor::motor() {
    pwm_pin = "Uninit";
    dir_pin = "Uninit";
}

motor::~motor() {

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
    gp = GPIOoo::getInstance();
    const char *pin_names[2];
    pin_names[0] = pwm_pin.toStdString().c_str();
    pin_names[1] = dir_pin.toStdString().c_str();
    motor_pin = gp->claim((char **)pin_names, 2,
                          GPIOoo::gpioWriteSemantics::gpioWrite, GPIOoo::gpioFlags::gpioExclusive);
};

