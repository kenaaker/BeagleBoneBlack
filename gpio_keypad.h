#ifndef GPIO_KEYPAD_H
#define GPIO_KEYPAD_H

#include <QObject>
#include <QSocketNotifier>
#include <QString>
#include <QFile>
#include "adafruit_bbio_gpio.h"

class gpio_keypad : public QObject {
    Q_OBJECT
public:
    gpio_keypad(QString sw_pin, QString in_key_name);
    ~gpio_keypad();
    int keypad_fd(void);            /* Return the file descriptor for the keypad interrupt device */
    QString const keyname(void);    /* Return the name of the key for this object */
private:
    Adafruit_bbio_gpio *this_gpio;  /* GPIO object for this pin */
    QFile keypad_value;             /* GPIO keypad value file for keypad file. */
    QString key_name;               /* User name for this key */
    QSocketNotifier *keypad_notifier;
    char current_value;    /* The last value read from the GPIO */
public slots:
    void ready_read(int);
};

#endif // GPIO_KEYPAD_H
