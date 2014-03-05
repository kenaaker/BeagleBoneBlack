#include "motor_control.h"
#include "ui_motor_control.h"
#include "gpio_sensor.h"
#include <QTimer>


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
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_sensor_display()));
    timer->start(100);
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
    QString light_number = QString::number(sr1->sensor_read());
    ui->light_sensor_display->setText(light_number);
}
