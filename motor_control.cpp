#include "motor_control.h"
#include "ui_motor_control.h"

motor_control::motor_control(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::motor_control)
{
    ui->setupUi(this);
    ui->motor_a_stop->setChecked(true);
    ui->motor_b_stop->setChecked(true);
    m_dca = motor(e_motor_id::e_motor_a);
}

motor_control::~motor_control()
{
    delete ui;
}

void motor_control::on_actionQuit_triggered()
{
    close();
}
