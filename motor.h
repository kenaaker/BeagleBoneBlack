#ifndef MOTOR_H
#define MOTOR_H
#include "adafruit_bbio_pwm.h"

#define motor_a_pwm_pin "P8_13";
#define motor_a_dir_pin "P8_14";
#define motor_b_pwm_pin "P8_19";
#define motor_b_dir_pin "P8_18";
#define motor_c_pwm_pin "?????";
#define motor_c_dir_pin "?????";
#define motor_d_pwm_pin "?????";
#define motor_d_dir_pin "?????";

enum class e_motor_id {
    e_motor_a,
    e_motor_b,
    e_motor_c,
    e_motor_d
};

class motor {

public:
    motor();
    motor(e_motor_id which_motor);
    ~motor();
    void motor_run(int8_t speed);
    void motor_stop(void);
    QString pwm_pin;
    QString dir_pin;

private:
    e_motor_id motor_id;
    int8_t motor_speed;         /* negative motor speed is reverse rotation */
    /* Interfaces to GPIO stuff */
    Adafruit_bbio_pwm *dc;      /* Pulse Width Modulated motor control for motor */
};

#endif // MOTOR_H
