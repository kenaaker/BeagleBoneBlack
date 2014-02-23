#include "motor_control.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    motor_control w;
    w.show();

    return a.exec();
}
