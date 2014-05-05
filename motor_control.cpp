#include "motor_control.h"
#include "ui_motor_control.h"
#include "gpio_sensor.h"
#include <QTimer>
#include <QString>

motor_control::motor_control(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::motor_control)
{
    ui->setupUi(this);
    ui->motor_a_stop->setChecked(true);
    ui->motor_b_stop->setChecked(true);
    m_dca = new motor(e_motor_id::e_motor_a);
    m_dcb = new motor(e_motor_id::e_motor_b);
    sr1 = new gpio_sensor("P9_25", "P9_39");
    sr2 = new gpio_sensor("P9_27", "P9_40");
    keypad_sw1 = new gpio_keypad("P8_39", "SW_1");
    keypad_a = new gpio_keypad("P8_32", "A");
    keypad_b = new gpio_keypad("P8_33", "B");
    keypad_sw2 = new gpio_keypad("P8_34", "SW_2");
    keypad_sw3 = new gpio_keypad("P8_35", "SW_3");
    keypad_sw4 = new gpio_keypad("P8_38", "SW_4");
    keypad_sw5 = new gpio_keypad("P8_37", "SW_5");
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_sensor_display()));
    timer->start(50);
    current_timer_count = 0;
    lowest_reading = 100000;
    highest_reading = 0;
}

motor_control::~motor_control()
{
    delete sr1;
    delete sr2;
    delete m_dcb;
    delete m_dca;
    delete ui;
}

void motor_control::on_actionQuit_triggered()
{
    close();
}

void motor_control::on_motor_a_start_clicked()
{
    ui->motor_a_speed->setValue(10);
}

void motor_control::on_motor_a_stop_clicked()
{
    ui->motor_a_speed->setValue(0);
}
void motor_control::on_motor_b_start_clicked()
{
    ui->motor_b_speed->setValue(20);
}

void motor_control::on_motor_b_stop_clicked()
{
    ui->motor_b_speed->setValue(0);
}

void motor_control::on_motor_a_speed_valueChanged(int position)
{
    m_dca->motor_run(position);
    ui->motor_a_start->setChecked(position != 0);
    ui->motor_a_stop->setChecked(position == 0);
}

void motor_control::on_motor_b_speed_valueChanged(int position)
{
    m_dcb->motor_run(position);
    ui->motor_b_start->setChecked(position != 0);
    ui->motor_b_stop->setChecked(position == 0);
}

void motor_control::update_sensor_display(void) {
    unsigned int current_reading = sr2->sensor_read();
    ++current_timer_count;
    if ((current_timer_count % 100) == 0) {
        lowest_reading = 10000;
        highest_reading = 0;
    } /* endif */
    QString light_number = QString::number(lowest_reading);
    ui->light_sensor_display_low->setText(light_number);
    light_number = QString::number(current_reading);
    ui->light_sensor_display_current->setText(light_number);
    light_number = QString::number(highest_reading);
    ui->light_sensor_display_high->setText(light_number);
    if (current_reading < lowest_reading) {
        lowest_reading = current_reading;
    } /* endif */
    if (current_reading > highest_reading) {
        highest_reading = current_reading;
    } /* endif */
}
