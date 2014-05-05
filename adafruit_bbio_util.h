#ifndef ADAFRUIT_BBIO_UTIL_H
#define ADAFRUIT_BBIO_UTIL_H

using namespace std;
#include <string>
#include <list>
#include <initializer_list>
#include <algorithm>

class pins_table {
public:
    pins_table();
    ~pins_table();
    int gpio_by_key(const string &key);
    int gpio_by_name(const string &name);
    string ain_by_key(const string &key);
    string ain_by_name(const string &name);
    string pwm_key_by_key(const string &key);
    string pwm_key_by_name(const string &name);
    int gpio_number(const string &key);
    int adc_ain_number(const string &n);

private:
    typedef struct pins_entry {
        string name;
        string key;
        int16_t gpio;
        int16_t pwm_mux_mode;
        int16_t ain;
    } pins_entry_t;
    list<pins_entry_t> pins;
};
#ifdef ADAFRUIT_BBIO_UTIL_LIB
string build_path(const string &partial_path, const string &prefix);
int load_device_tree(const string &tree_add_name);
int unload_device_tree(const string &tree_del_name);
pins_table pin_lookup;
string control_directory;
#else
extern string build_path(const string &partial_path, const string &prefix);
extern int load_device_tree(const string &tree_add_name);
extern int unload_device_tree(const string &tree_del_name);
extern pins_table pin_lookup;
extern string control_directory;
#endif

#endif // ADAFRUIT_BBIO_UTIL_H
