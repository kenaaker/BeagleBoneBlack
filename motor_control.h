#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <QMainWindow>
#include <motor.h>

namespace Ui {
class motor_control;
}

class motor_control : public QMainWindow {
    Q_OBJECT

public:
    explicit motor_control(QWidget *parent = 0);
    ~motor_control();

private slots:
    void on_actionQuit_triggered();

private:
    Ui::motor_control *ui;
    motor m_dca;
    motor m_dcb;
};

#endif // MOTOR_CONTROL_H
