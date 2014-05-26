#ifndef MOTOR_H
#define MOTOR_H
#include <QElapsedTimer>
#include <QTimer>

#include "adafruit_bbio_pwm.h"
#include "adafruit_bbio_gpio.h"

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

class motor : public QObject {
    Q_OBJECT

public:
    motor();
    motor(e_motor_id which_motor);
    ~motor();
    void motor_run(int8_t speed);
    void motor_stop(void);
    void motor_pause(void);
    void motor_resume(void);
    int8_t motor_get_speed();
    void set_motor_rotation_speed(float rpm);
    void set_motor_position(int pos_degrees);
    int position();             /* Return the rotation position */
    void motor_goto_pos(int pos_degrees, int speed);

signals:
    void movement_done(int pos_degrees);
private:
    static const int dest_fuzz = 2;
    QString pwm_pin;
    QString dir_pin;
    int gpio_dir_pin;
    e_motor_id motor_id;
    int8_t motor_speed;         /* negative motor speed is reverse rotation */
    int8_t suspended_motor_speed;/* negative motor speed is reverse rotation */
    /* Interfaces to GPIO stuff */
    Adafruit_bbio_pwm *dc;      /* Pulse Width Modulated motor control for motor */
    Adafruit_bbio_gpio *dir;    /* Direction control GPIO pin */
    QElapsedTimer run_start_time;
    QTimer movement_timer;      /* Timer used to monitor motor moving to position */
    int m_position;             /* Estimated motor position in degrees */
    float motor_rotation_speed; /* Motor rotation speed in RPM (fractional for slow motor) */
    int destination_pos;        /* motor movement destination in degrees */
private slots:
    void movement_check(void);
};

#endif // MOTOR_H
