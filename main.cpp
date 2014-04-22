
#include <QApplication>

#include "gpio_keypad.h"
#include "motor_control.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    motor_control w;
    w.show();

    return a.exec();
}
