#include <QFile>
#include <QTextStream>
#include <QString>
#include <list>
#include <sstream>
#include <iostream>


#include "adafruit_bbio_gpio.h"

static inline int string_to_int(string s)
{
    stringstream ss(s);
    int x;
    ss >> x;
    return x;
}

static inline string int_to_string(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}

Adafruit_bbio_gpio::Adafruit_bbio_gpio() {
    gpio_number = 9999;
    gpio_key = "uninit";
    gpio_directory = "";
    io_direction = io_input;
}
Adafruit_bbio_gpio::Adafruit_bbio_gpio(const string &in_gpio_key) {
    int tentative_gpio_number = gpio_export(in_gpio_key);
    if (tentative_gpio_number < 0) {
        abort();
    } else {
        gpio_number = tentative_gpio_number;
        gpio_key = in_gpio_key;
        gpio_directory = QDir("/sys/class/gpio/gpio" + QString::number(gpio_number) + "/");
        io_direction = io_input;
    } /* endif */
} /* constructor */

Adafruit_bbio_gpio::~Adafruit_bbio_gpio(void) {
    static const string gpio_unexport_filename = "/sys/class/gpio/unexport";
    // Close the value file descriptor for this GPIO, if one exists

    QFile gpio_unexport(QString::fromStdString(gpio_unexport_filename));
    if (gpio_unexport.open(QIODevice::WriteOnly)) {
        QTextStream unexport_stream(&gpio_unexport);
        unexport_stream << gpio_number;
        gpio_unexport.close();
    } /* endif */
} /* destructor */

int Adafruit_bbio_gpio::gpio_export(const string &in_gpio_key) {
    static const string gpio_export_filename = "/sys/class/gpio/export";
    int rc = -1;
    gpio_number = pin_lookup.gpio_by_key(in_gpio_key);

    if (gpio_number == -1) {
        rc = gpio_number;
    } else {
        QFile gpio_export(QString::fromStdString(gpio_export_filename));
        if (!gpio_export.open(QIODevice::WriteOnly)) {
            rc = -1;
        } else {
            QTextStream export_stream(&gpio_export);
            export_stream << gpio_number;
            gpio_export.close();
            rc = gpio_number;
        } /* endif */
    } /* endif */
    return rc;
} /* export GPIO pin to enable */

int Adafruit_bbio_gpio::gpio_set_direction(const string &direction) {
    int rc = -1;

//    cout << " gpio_directory = \"" << gpio_directory.path().toStdString() + "/direction" << "\"" << endl;

    QFile direction_file(gpio_directory.path() + "/direction");
    if (!direction_file.open(QIODevice::WriteOnly)) {
        rc = -1;
    } else {
        QTextStream out_direction(&direction_file);
        out_direction << QString::fromStdString(direction);
        direction_file.close();
        rc = 1;
    } /* endif */

    return rc;
} /* gpio_set_direction */

string Adafruit_bbio_gpio::gpio_get_direction() {
    QFile direction_file(gpio_directory.path() + "/direction");
    QString direction_str;
    if (direction_file.open(QIODevice::ReadOnly)) {
        QTextStream in_direction(&direction_file);
        in_direction >> direction_str;
        direction_file.close();
    } /* endif */
    return direction_str.toStdString();
} /* gpio_get_direction */

int Adafruit_bbio_gpio::gpio_set_value(const string &value) {
    int rc=-1;
//    cout << " gpio_directory = \"" << gpio_directory.path().toStdString() + "/value" << "\"" << endl;

    QFile value_file(gpio_directory.path() + "/value");
    if (!value_file.open(QIODevice::WriteOnly)) {
        rc = -1;
    } else {
        QTextStream out_value(&value_file);
        out_value << QString::fromStdString(value);
//        cout << " gpio_set_value = \"" << value << "\"" << endl;
        value_file.close();
        rc = 1;
    } /* endif */
    return rc;
} /* gpio_set_value */

string Adafruit_bbio_gpio::gpio_get_value() {
    QFile value_file(gpio_directory.path() + "/value");
    unsigned char value = '0';
    string value_str;
    if (value_file.open(QIODevice::ReadOnly)) {
        QDataStream in_value(&value_file);
        in_value >> value;
        value_str = value;
        value_file.close();
    } /* endif */
    return value_str;
} /* gpio_get_value */

// Return the file path of this gpio for the value file */
string Adafruit_bbio_gpio::gpio_get_path() {
    return (gpio_directory.path() + "/value").toStdString();
} /* gpio_get_path */

int Adafruit_bbio_gpio::gpio_set_edge(const string &edge_name) {
    int rc=-1;
//    cout << " gpio_directory = \"" << gpio_directory.path().toStdString() + "/value" << "\"" << endl;

    QFile edge_file(gpio_directory.path() + "/edge");
    if (!edge_file.open(QIODevice::WriteOnly)) {
        rc = -1;
    } else {
        QTextStream out_edge(&edge_file);
        out_edge << QString::fromStdString(edge_name);
//        cout << " gpio_set_edge = \"" << edge_name << "\"" << endl;
        edge_file.close();
        rc = 1;
    } /* endif */
    return rc;
} /* gpio_set_edge */
