#include "adafruit_bbio_adc.h"
#include <iostream>
#include <QFile>
#include <QTextStream>

Adafruit_bbio_adc::Adafruit_bbio_adc(const string &in_adc_key) {
    string l_adc_name;
    string adc_prefix_dir;
    if (load_device_tree("cape-bone-iio")) {
        ocp_dir = build_path("/sys/devices/", "ocp")+"/";
        cout << " ocp_dir = \"" << ocp_dir << "\"" << endl;
        adc_prefix_dir = ocp_dir + "/helper_";
        adc_file_path = adc_prefix_dir + "/AIN0";
        cout << " adc_prefix_dir = \"" << adc_prefix_dir << "\"" << endl;
        cout << " adc_file_path = \"" << adc_file_path << "\"" << endl;
        /* Now test open the file */
        adc_value_file.setFileName(QString::fromStdString(adc_file_path));
        if (!adc_value_file.open(QIODevice::ReadWrite)) {
            unload_device_tree("cape-bone-iio");
            abort();
        } else {
            ain = pin_lookup.gpio_by_key(in_adc_key);
            cout << " ain = " << ain << endl;
            if (ain < 0) {
                abort();
            } /* endif */
        } /* endif */
    } /* endif */
} /* constructor */

Adafruit_bbio_adc::~Adafruit_bbio_adc() {
    adc_value_file.close();
    unload_device_tree("cape-bone-iio");
} /* destructor */

int Adafruit_bbio_adc::adc_read_value() {
    int adc_value;

    adc_value_file.seek(0);
    QTextStream in_adc(&adc_value_file);
    in_adc >> adc_value;

    return adc_value;
} /* adc_read_value */
