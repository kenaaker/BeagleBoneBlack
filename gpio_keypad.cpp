
#include "gpio_keypad.h"
#include <QDebug>

gpio_keypad::gpio_keypad(QString sw_pin, QString in_key_name) {

    this_gpio = new Adafruit_bbio_gpio(sw_pin.toStdString());
    if (!this_gpio) {
        abort();
    } else {
        QString gpio_value_path;
        key_name = in_key_name;
        gpio_value_path = QString::fromStdString(this_gpio->gpio_get_path());
        qDebug() << "keypad path=" << gpio_value_path;
        keypad_value.setFileName(gpio_value_path);      /* Set up the value file */
        this_gpio->gpio_set_direction("in");
        this_gpio->gpio_set_edge("both");             /* Interrupt on rising edge */
        keypad_value.open(QFile::ReadOnly);
        keypad_notifier = new QSocketNotifier(keypad_value.handle(), QSocketNotifier::Exception);
        keypad_notifier->setEnabled(true);
        connect(keypad_notifier, SIGNAL(activated(int)), this, SLOT(ready_read(int)));
    } /* endif */
}

gpio_keypad::~gpio_keypad() {
    keypad_value.close();
    this_gpio->gpio_set_edge("none");             /* Don't generate interrupts. */
    delete keypad_notifier;
    delete this_gpio;
}

int gpio_keypad::keypad_fd(void) {
    return keypad_value.handle();
} /* keypad_fd */

QString const gpio_keypad::keyname(void) {
    return(key_name);
} /* keyname */

void gpio_keypad::ready_read(int) {
    QByteArray line;
    keypad_value.seek(0);
    char last_value = current_value;
    line = keypad_value.readAll();
    qDebug() << "bytes_read=" << line.size();
    if (line.size() < 1) {
        abort();
    } else {
        current_value = line[0];
        emit button_pushed(current_value);
    } /* endif */
    if (current_value != last_value) {
        qDebug() << "key" << key_name << "switch value changed, old=" << last_value << "current_value" << current_value;
    } /* endif */
} /* ready_read */

