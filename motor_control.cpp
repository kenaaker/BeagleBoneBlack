#include "motor_control.h"
#include "ui_motor_control.h"

motor_control::motor_control(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::motor_control)
{
    ui->setupUi(this);
    ui->motor_a_stop->setChecked(true);
    ui->motor_b_stop->setChecked(true);
    m_dca = new motor(e_motor_id::e_motor_a);
    m_dcb = new motor(e_motor_id::e_motor_b);
    m_dca->motor_run(20.0);
    m_dcb->motor_run(10.0);
}

motor_control::~motor_control()
{
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
    m_dca->motor_run(20);
}

void motor_control::on_motor_a_stop_clicked()
{
    m_dca->motor_run(0);
}
void motor_control::on_motor_b_start_clicked()
{
    m_dcb->motor_run(20);
}

void motor_control::on_motor_b_stop_clicked()
{
    m_dcb->motor_run(0);
}
