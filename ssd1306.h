#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>

typedef enum {
    SSD1306_128_64 = 1,
    SSD1306_128_32 = 2,
    SSD1306_96_16 = 3
} SSD1306_Type;

class SSD1306 {

public:
    SSD1306(unsigned char address, SSD1306_Type type);
    ~SSD1306();

    int openDevice(const char *bus);
    void setBuffer(unsigned char *bitmap_buffer);
    void closeDevice(void);
    int initDevice(void);

    uint8_t getWidth();
    uint8_t getHeight();
    void pushDisplay(void);

private:
    unsigned char _address;
    int _i2cFileHandler;
    SSD1306_Type _type;
    unsigned char *buffer;      /* Bitmap buffer */

    void sendCommand(unsigned char command);
};

#endif // SSD1306_H
