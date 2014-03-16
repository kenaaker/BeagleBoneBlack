#include "adafruit_bbio_pwm.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <time.h>
#include <string>


void  Adafruit_bbio_pwm::set_frequency(float in_freq) {
    if (in_freq >= 0.0) {
        QTextStream out(&period_file);
        out << 1.0E9 / in_freq;
        freq = in_freq;
    } /* endif */
} /* set_frequency */

void Adafruit_bbio_pwm::set_duty_cycle(float in_duty) {
    if ((in_duty >= 0.0) && (in_duty <= 100.0)) {
        QTextStream out(&duty_file);
        out << ((1.0E9 / freq) * (in_duty / 100.0));
        duty_cycle_percent = in_duty;
    } /* endif */
    // cout << "set_duty_cycle " << in_duty << " duty_file_name = \"" << duty_file_name << endl;
}  /* set_duty_cycle */

void Adafruit_bbio_pwm::set_polarity(bool in_polarity) {
    QTextStream out(&polarity_file);
    out << in_polarity;
    polarity = in_polarity;
} /* set_polarity */

float Adafruit_bbio_pwm::get_frequency(void) {
    return freq;
} /* get_frequency */

float Adafruit_bbio_pwm::get_duty_cycle(void) {
    return duty_cycle_percent;
}  /* get_duty_cycle */

bool Adafruit_bbio_pwm::get_polarity(void) {
   return polarity;
} /* get_polarity */

Adafruit_bbio_pwm::Adafruit_bbio_pwm(const string &key) {
    string pwm_test_path;
    string l_pwm_name;

    if (load_device_tree("am33xx_pwm")) {
        ocp_dir = build_path("/sys/devices/", "ocp") + "/";
        //cout << " ocp_dir = \"" << ocp_dir << "\"" << endl;
        l_pwm_name = "bone_pwm_"+key;
        if (!load_device_tree(l_pwm_name)) {
            abort();
        } else {
            int wait_count=100;

            pwm_name = l_pwm_name;
            pwm_test_path = build_path(ocp_dir, "pwm_test_" + key);
            //cout << " pwm_test_path = \"" << pwm_test_path << "\"" << endl;
            period_file_name = pwm_test_path + "/period";
            period_file.setFileName(QString::fromStdString(period_file_name));
            duty_file_name = pwm_test_path + "/duty";
            //cout << " duty_file_name = \"" << duty_file_name << endl;
            duty_file.setFileName(QString::fromStdString(duty_file_name));
            polarity_file_name = pwm_test_path + "/polarity";
            polarity_file.setFileName(QString::fromStdString(polarity_file_name));
            /* Now open all the files */
            while((!period_file.open(QIODevice::ReadWrite)) && (wait_count > 0)) {
                nanosleep((const struct timespec[]){{0,200000000}},NULL);
                --wait_count;
            } /* endwhile */
            if (wait_count == 0) {
                unload_device_tree("bone_pwm_"+key);
                abort();
            } else {
                if (!duty_file.open(QIODevice::ReadWrite)) {
                    period_file.close();
                    unload_device_tree("bone_pwm_"+key);
                    abort();
                } else {
                    if (!polarity_file.open(QIODevice::ReadWrite)) {
                        duty_file.close();
                        period_file.close();
                        unload_device_tree("bone_pwm_"+key);
                        abort();
                    } else {
                        set_frequency(2000);
                        set_duty_cycle(0);
                        set_polarity(false);
                    } /* endif */
                } /* endif */
            } /* endif */

        } /* endif */
    } /* endif */

} /* Adafruit_bbio_pmw() */

Adafruit_bbio_pwm::~Adafruit_bbio_pwm() {
    unload_device_tree(pwm_name);
    period_file.close();
    duty_file.close();
    polarity_file.close();
}
