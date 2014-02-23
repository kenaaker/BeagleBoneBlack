#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <QMainWindow>

namespace Ui {
class motor_control;
}

class motor_control : public QMainWindow
{
    Q_OBJECT

public:
    explicit motor_control(QWidget *parent = 0);
    ~motor_control();

private:
    Ui::motor_control *ui;
};

#endif // MOTOR_CONTROL_H
