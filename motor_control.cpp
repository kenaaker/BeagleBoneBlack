#include "motor_control.h"
#include "ui_motor_control.h"

motor_control::motor_control(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::motor_control)
{
    ui->setupUi(this);
}

motor_control::~motor_control()
{
    delete ui;
}
