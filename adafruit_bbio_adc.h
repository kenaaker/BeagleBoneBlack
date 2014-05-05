#ifndef ADAFRUIT_BBIO_ADC_H
#define ADAFRUIT_BBIO_ADC_H

#include <QDir>
#include <QFile>
#include <QTimer>
#include <list>

using namespace std;
#include <string>
#include <list>

#include "adafruit_bbio_gpio.h"
#include "adafruit_bbio_util.h"

using namespace std;
#include <string>

class Adafruit_bbio_adc {

public:
    Adafruit_bbio_adc();
    Adafruit_bbio_adc(const string &in_adc_key);
    ~Adafruit_bbio_adc();
    int adc_read_value();
private:
    string ocp_dir;
    string adc_file_path;
    string ain;
    QFile adc_value_file;

};

#endif // ADAFRUIT_BBIO_ADC_H
