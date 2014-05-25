
#include <QtCore>
#include <QString>
#include <QtGlobal>
#include <QtCore/QDebug>

#include <motor.h>
#include "adafruit_bbio_pwm.h"

motor::motor() {
    pwm_pin = "Uninit";
    dir_pin = "Uninit";
    motor_rotation_speed = 1.0;
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
    m_position = 0;
    dir = new Adafruit_bbio_gpio(dir_pin.toStdString());
    dir->gpio_set_direction("out");
    dir->gpio_set_value("1");
    dc = new Adafruit_bbio_pwm(pwm_pin.toStdString());
    connect(&movement_timer, SIGNAL(timeout()), this, SLOT(movement_check()));
}

void motor::motor_run(int8_t speed) {
    uint8_t direction;
    uint8_t abs_speed;

    speed = (int8_t)qBound(-100, (int)speed, 100);
    direction = (speed > 0);

    abs_speed = abs(speed);
    m_position = position();        // Update the current position
    if (direction) {
        dir->gpio_set_value("0");
    } else {
        dir->gpio_set_value("1");
    } /* endif */
    dc->set_duty_cycle(abs_speed);
    if (abs_speed != 0) {
        run_start_time.start();
    } else {
        run_start_time.invalidate();
    } /* endif */
    motor_speed = speed;
}

void motor::motor_stop(void) {
    motor_run(0);
}

void motor::set_motor_rotation_speed(float rpm) {
    motor_rotation_speed = rpm;
}

void motor::set_motor_position(int pos_degrees) {
    m_position = pos_degrees;
}

int motor::position(void) {
    int calculated_position;
    qint64 since_start;
    if (run_start_time.isValid()) {
        since_start = run_start_time.nsecsElapsed();
        double seconds_since_start = ((double)since_start / 1E9);

        double fposition = seconds_since_start * (motor_rotation_speed * (double(motor_speed)/100.0) / 60. * 360.);
        calculated_position = round(fposition) + m_position;
    } else {
        calculated_position = m_position;
    } /* endif */

    return calculated_position % 360;
}

void motor::motor_goto_pos(int pos_degrees, int speed=30) {
    if (movement_timer.isActive()) {
        abort();
    } else {
        int rotation_delta;
        int curr_pos = abs((position() + 360) % 360);
        destination_pos = pos_degrees % 360;
        // qDebug() << "motor_goto_pos destination is" << destination_pos << "current pos is" << curr_pos;
        /* Calculate minimal rotation distance and direction, 0 <= n <= 180  dest < orig -> -move, dest > orig -> +move */
        rotation_delta = destination_pos - curr_pos;
        // qDebug() << "1 rotation delta is" << rotation_delta << "speed is " << speed;
        if (rotation_delta < 0) {
            speed = -speed;
        } /* endif */
        /* Now see if there's a shorter rotation, the other way */
        if (((destination_pos + 360) - curr_pos) < 180) {
            speed = -speed;
        } /* endif */
        if (rotation_delta > 180) {
            speed = -speed;
        } /* endif */
        // qDebug() << "2 rotation delta is" << rotation_delta << "speed is " << speed;
        movement_timer.start(25);               /* Start a 25 millisecond timer to monitor motor position */
        motor_run(speed);
    } /* endif */
}

/* Entered from timer to check if movement is finished */
/* Emits movement_done when it decides the movement is finished */
void motor::movement_check(void) {
    int curr_pos = abs((position() + 360) % 360);
    //qDebug() << "Movement_check destination is" << destination_pos << "current pos is" << curr_pos;
    if ((curr_pos >= destination_pos-dest_fuzz) && (curr_pos <=destination_pos+dest_fuzz)) {
        motor_stop();
        movement_timer.stop();
        emit movement_done(m_position);
    } /* endif */
}
