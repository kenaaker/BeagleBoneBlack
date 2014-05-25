#define ADAFRUIT_BBIO_UTIL_LIB
#include "adafruit_bbio_util.h"
#include <QString>
#include <QStringList>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <iostream>

pins_table::pins_table() {
    initializer_list<pins_entry_t> p_list = {
        { "USR0", "USR0", 53, -1, -1},
        { "USR1", "USR1", 54, -1, -1},
        { "USR2", "USR2", 55, -1, -1},
        { "USR3", "USR3", 56, -1, -1},
        { "DGND", "P8_1", 0, -1, -1},
        { "DGND", "P8_2", 0, -1, -1},
        { "GPIO1_6", "P8_3", 38, -1, -1},
        { "GPIO1_7", "P8_4", 39, -1, -1},
        { "GPIO1_2", "P8_5", 34, -1, -1},
        { "GPIO1_3", "P8_6", 35, -1, -1},
        { "TIMER4", "P8_7", 66, -1, -1},
        { "TIMER7", "P8_8", 67, -1, -1},
        { "TIMER5", "P8_9", 69, -1, -1},
        { "TIMER6", "P8_10", 68, -1, -1},
        { "GPIO1_13", "P8_11", 45, -1, -1},
        { "GPIO1_12", "P8_12", 44, -1, -1},
        { "EHRPWM2B", "P8_13", 23, 4, -1},
        { "GPIO0_26", "P8_14", 26, -1, -1},
        { "GPIO1_15", "P8_15", 47, -1, -1},
        { "GPIO1_14", "P8_16", 46, -1, -1},
        { "GPIO0_27", "P8_17", 27, -1, -1},
        { "GPIO2_1", "P8_18", 65, -1, -1},
        { "EHRPWM2A", "P8_19", 22, 4, -1},
        { "GPIO1_31", "P8_20", 63, -1, -1},
        { "GPIO1_30", "P8_21", 62, -1, -1},
        { "GPIO1_5", "P8_22", 37, -1, -1},
        { "GPIO1_4", "P8_23", 36, -1, -1},
        { "GPIO1_1", "P8_24", 33, -1, -1},
        { "GPIO1_0", "P8_25", 32, -1, -1},
        { "GPIO1_29", "P8_26", 61, -1, -1},
        { "GPIO2_22", "P8_27", 86, -1, -1},
        { "GPIO2_24", "P8_28", 88, -1, -1},
        { "GPIO2_23", "P8_29", 87, -1, -1},
        { "GPIO2_25", "P8_30", 89, -1, -1},
        { "UART5_CTSN", "P8_31", 10, -1, -1},
        { "UART5_RTSN", "P8_32", 11, -1, -1},
        { "UART4_RTSN", "P8_33", 9, -1, -1},
        { "UART3_RTSN", "P8_34", 81, 2, -1},
        { "UART4_CTSN", "P8_35", 8, -1, -1},
        { "UART3_CTSN", "P8_36", 80, 2, -1},
        { "UART5_TXD", "P8_37", 78, -1, -1},
        { "UART5_RXD", "P8_38", 79, -1, -1},
        { "GPIO2_12", "P8_39", 76, -1, -1},
        { "GPIO2_13", "P8_40", 77, -1, -1},
        { "GPIO2_10", "P8_41", 74, -1, -1},
        { "GPIO2_11", "P8_42", 75, -1, -1},
        { "GPIO2_8", "P8_43", 72, -1, -1},
        { "GPIO2_9", "P8_44", 73, -1, -1},
        { "GPIO2_6", "P8_45", 70, 3, -1},
        { "GPIO2_7", "P8_46", 71, 3, -1},
        { "DGND", "P9_1", 0, -1, -1},
        { "DGND", "P9_2", 0, -1, -1},
        { "VDD_3V3", "P9_3", 0, -1, -1},
        { "VDD_3V3", "P9_4", 0, -1, -1},
        { "VDD_5V", "P9_5", 0, -1, -1},
        { "VDD_5V", "P9_6", 0, -1, -1},
        { "SYS_5V", "P9_7", 0, -1, -1},
        { "SYS_5V", "P9_8", 0, -1, -1},
        { "PWR_BUT", "P9_9", 0, -1, -1},
        { "SYS_RESETn", "P9_10", 0, -1, -1},
        { "UART4_RXD", "P9_11", 30, -1, -1},
        { "GPIO1_28", "P9_12", 60, -1, -1},
        { "UART4_TXD", "P9_13", 31, -1, -1},
        { "EHRPWM1A", "P9_14", 50, 6, -1},
        { "GPIO1_16", "P9_15", 48, -1, -1},
        { "EHRPWM1B", "P9_16", 51, 6, -1},
        { "I2C1_SCL", "P9_17", 5, -1, -1},
        { "I2C1_SDA", "P9_18", 4, -1, -1},
        { "I2C2_SCL", "P9_19", 13, -1, -1},
        { "I2C2_SDA", "P9_20", 12, -1, -1},
        { "UART2_TXD", "P9_21", 3, 3, -1},
        { "UART2_RXD", "P9_22", 2, 3, -1},
        { "GPIO1_17", "P9_23", 49, -1, -1},
        { "UART1_TXD", "P9_24", 15, -1, -1},
        { "GPIO3_21", "P9_25", 117, -1, -1},
        { "UART1_RXD", "P9_26", 14, -1, -1},
        { "GPIO3_19", "P9_27", 115, -1, -1},
        { "SPI1_CS0", "P9_28", 113, 4, -1},
        { "SPI1_D0", "P9_29", 111, 1, -1},
        { "SPI1_D1", "P9_30", 112, -1, -1},
        { "SPI1_SCLK", "P9_31", 110, 1, -1},
        { "VDD_ADC", "P9_32", 0, -1, -1},
        { "AIN4", "P9_33", 0, -1, 4},
        { "GNDA_ADC", "P9_34", 0, -1, -1},
        { "AIN6", "P9_35", 0, -1, 6},
        { "AIN5", "P9_36", 0, -1, 5},
        { "AIN2", "P9_37", 0, -1, 2},
        { "AIN3", "P9_38", 0, -1, 3},
        { "AIN0", "P9_39", 0, -1, 0},
        { "AIN1", "P9_40", 0, -1, 1},
        { "CLKOUT2", "P9_41", 20, -1, -1},
        { "GPIO0_7", "P9_42", 7, 0, -1},
        { "DGND", "P9_43", 0, -1, -1},
        { "DGND", "P9_44", 0, -1, -1},
        { "DGND", "P9_45", 0, -1, -1},
        { "DGND", "P9_46", 0, -1, -1}
    };
    pins.insert(pins.end(), p_list.begin(), p_list.end());
} // pins_table constructor

pins_table::~pins_table() {

} // pins_table destructor

int pins_table::gpio_by_key(const string &key) {
    list<pins_entry_t>::iterator p_i;
    p_i = find_if(pins.begin(), pins.end(), [&](pins_entry &p){return p.key == key;});
    if (p_i != pins.end()) {
        return p_i->gpio;
    } else {
        return -1;
    } /* endif */
}

int pins_table::gpio_by_name(const string &name) {
    list<pins_entry_t>::iterator p_i;
    p_i = find_if(pins.begin(), pins.end(), [&](pins_entry &p){return p.name == name;});
    if (p_i != pins.end()) {
        return p_i->gpio;
    } else {
        return -1;
    } /* endif */
}

string pins_table::ain_by_key(const string &key) {
    list<pins_entry_t>::iterator p_i;
    p_i = find_if(pins.begin(), pins.end(), [&](pins_entry &p){return p.key == key;});
    if (p_i != pins.end()) {
        return p_i->name;
    } else {
        return "";
    } /* endif */
}

string pins_table::ain_by_name(const string &name) {
    list<pins_entry_t>::iterator p_i;
    p_i = find_if(pins.begin(), pins.end(), [&](pins_entry &p){return p.name == name;});
    if (p_i != pins.end()) {
        return p_i->name;
    } else {
        return "";
    } /* endif */
}

string build_path(const string &partial_path, const string &prefix) {
    if (!QDir(QString::fromStdString(partial_path)).exists()) {
        return "";
    } else {
//        cout << " build_path partial = \"" << partial_path << "\"" << endl;
//        cout << " build_path prefix = \"" << prefix << "\"" << endl;
        QStringList dir_filters(QString::fromStdString(prefix)+"*");
        QDir start_dir(QString::fromStdString(partial_path));
        QStringList matches = start_dir.entryList(dir_filters, QDir::Dirs);
//        cout << " filters = \"" << qPrintable(QString::fromStdString(prefix)+"*") << "\"" << endl;
//        cout << " filtered path = \"" << partial_path + qPrintable(QString::fromStdString(prefix)+"*") << "\"" << endl;
        if (matches.empty()) {
            return "";
        } else {
//            cout << " build_path return = \"" << partial_path+matches[0].toStdString() << "\"" << endl;
            return partial_path + matches[0].toStdString();
        } /* endif */
    } /* endif */
} /* build_path */

int load_device_tree(const string &tree_add_name) {
    string dev_tree_name;
    QFile tree_file;
    int rc = -1;

    dev_tree_name = build_path("/sys/devices/", "bone_capemgr") + "/slots";
    control_directory = dev_tree_name;
    tree_file.setFileName(QString::fromStdString(dev_tree_name));
    if (!tree_file.open(QIODevice::ReadWrite)) {
        rc = -EIO;
    } else {
        while (!tree_file.atEnd()) {
            QByteArray line = tree_file.readLine();
            if (line.isEmpty()) {
                break;
            }
            string check_string(line.constData(), line.length());
            if (check_string.find(tree_add_name) != string::npos) {
                rc = 1; /* Already loaded indicator */
                break;
            } /* endif */
        } /* endwhile */
        if (rc != 1) {
            QByteArray line(tree_add_name.c_str(), tree_add_name.length());
            tree_file.write(line);
            rc = 1;
            nanosleep((const struct timespec[]){{0,200000000}},NULL);
        } /* endif */
        tree_file.close();
    } /* endif */
    return rc;
} /* load_device_tree */

int unload_device_tree(const string &tree_del_name) {
    QFile tree_file;
    QTextStream in_out(&tree_file);
    int rc = -1;

    tree_file.setFileName(QString::fromStdString(control_directory));
    if (!tree_file.open(QIODevice::ReadWrite)) {
        rc = -EIO;
    } else {
        while (!tree_file.atEnd()) {
            QString check_string = tree_file.readLine();
            if (check_string.isEmpty()) {
                break;
            } /* endif */
            if (check_string.contains(QString::fromStdString(tree_del_name))) { /* It IS loaded */
//                size_t colon_pos = check_string.indexOf(":");
//                size_t num_pos = check_string.indexOf(QRegExp("[0-9]+"));
//                QString slot_line = "-" + check_string.mid(num_pos, colon_pos-num_pos);
//                in_out << slot_line;
                rc = 1;
                break;
            } /* endif */
        } /* endwhile */
        tree_file.close();
    } /* endif */
    return rc;
} /* unload_device_tree */
