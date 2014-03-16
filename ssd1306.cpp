#include "ssd1306.h"

//#include <linux/i2c-dev.h>
#include "i2c-dev.lm-sensors.h"
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SSD1306_I2C_ADDRESS   0x3D	// 011110+SA0+RW

#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDRESS 0x21
#define SSD1306_PAGEADDRESS 0x22

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

SSD1306::SSD1306(unsigned char address, SSD1306_Type type) {
    //PixelCoordonate width = 0, height = 0;

    _address = address;
    _type = type;
    _i2cFileHandler = 0;
    buffer = (unsigned char *)NULL;
}

SSD1306::~SSD1306() {
}

void SSD1306::setBuffer(unsigned char *bitmap_buffer) {
    buffer = bitmap_buffer;
};

int SSD1306::openDevice(const char *bus) {
    _i2cFileHandler = open(bus, O_RDWR);
    if (_i2cFileHandler <= 0) {
        printf("problem to open the bus\n");
        return 1;
    }

    if (ioctl(_i2cFileHandler, I2C_SLAVE, _address) != 0) {
        printf("problem to set the slave address\n");
        return 1;
    }
    return 0;
}

void SSD1306::closeDevice(void) {
    close(_i2cFileHandler);
}

void SSD1306::sendCommand(unsigned char command) {
    unsigned char bufferCommand[2] = { 0x00, command };

    if (write(_i2cFileHandler, bufferCommand, sizeof(bufferCommand)) != sizeof(bufferCommand)) {
        printf("problem with %d\n", command);
    }
}

int SSD1306::initDevice(void) {
    int vccstate = SSD1306_SWITCHCAPVCC;

    // Init sequence for 128x64 OLED module
    this->sendCommand(SSD1306_DISPLAYOFF);                    // 0xAE
    this->sendCommand(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
    this->sendCommand(0x80);                                  // the suggested ratio 0x80
    this->sendCommand(SSD1306_SETMULTIPLEX);                  // 0xA8
    switch (_type) {
        case SSD1306_128_64:
            this->sendCommand(0x3F);
            break;
        case SSD1306_128_32:
            this->sendCommand(0x1F);
            break;
        case SSD1306_96_16:
            this->sendCommand(0x0F);
            break;
    }
    this->sendCommand(SSD1306_SETDISPLAYOFFSET);              // 0xD3
    this->sendCommand(0x0);                                   // no offset
    if (_type == SSD1306_96_16) {
        this->sendCommand(SSD1306_SETSTARTLINE | 0x08);            // line #0
    } else {
        this->sendCommand(SSD1306_SETSTARTLINE | 0x0);            // line #0
    }
    this->sendCommand(SSD1306_CHARGEPUMP);                    // 0x8D
    if (vccstate == SSD1306_EXTERNALVCC) {
        this->sendCommand(0x10);
    } else {
        this->sendCommand(0x14);
    }
    this->sendCommand(SSD1306_MEMORYMODE);                    // 0x20
    this->sendCommand(0x00);                                  // 0x0 act like ks0108
    this->sendCommand(SSD1306_COLUMNADDRESS);                 // 0x21
    this->sendCommand(0x00);                                  // start column
    switch (_type) {
        case SSD1306_128_64:
            this->sendCommand(0x7F);                                  // end column 127
            break;
        case SSD1306_128_32:
            this->sendCommand(0x7F);                                  // end column 127
            break;
        case SSD1306_96_16:
            this->sendCommand(95);                                  // end column 95
            break;
    }
    this->sendCommand(SSD1306_PAGEADDRESS);                   // 0x22
    this->sendCommand(0x00);                                  // start page
    switch (_type) {
        case SSD1306_128_64:
            this->sendCommand(0x07);                                  // end page 7
            break;
        case SSD1306_128_32:
            this->sendCommand(0x07);                                  // end page 7
            break;
        case SSD1306_96_16:
            this->sendCommand(0x01);                                  // end page 1
            break;
    }
    this->sendCommand(SSD1306_SEGREMAP | 0x1);
    this->sendCommand(SSD1306_COMSCANDEC);
    this->sendCommand(SSD1306_SETCOMPINS);                    // 0xDA
    switch (_type) {
        case SSD1306_128_64:
            this->sendCommand(0x12);
            break;
        case SSD1306_128_32:
            this->sendCommand(0x02);
            break;
        case SSD1306_96_16:
            this->sendCommand(0x02);
            break;
    }
    this->sendCommand(SSD1306_SETCONTRAST);                   // 0x81
    switch (_type) {
        case SSD1306_128_64:
            if (vccstate == SSD1306_EXTERNALVCC) {
                this->sendCommand(0x9F);
            } else {
                this->sendCommand(0xCF);
            }
            break;
        case SSD1306_128_32:
            this->sendCommand(0x8F);
            break;
        case SSD1306_96_16:
            if (vccstate == SSD1306_EXTERNALVCC) {
                this->sendCommand(0x10);
            } else {
                this->sendCommand(0xAF);
            }
            break;
    }
    this->sendCommand(SSD1306_SETPRECHARGE);                  // 0xd9
    if (vccstate == SSD1306_EXTERNALVCC) {
        this->sendCommand(0x22);
    } else {
        this->sendCommand(0xF1);
    }
    this->sendCommand(SSD1306_SETVCOMDETECT);                 // 0xDB
    this->sendCommand(0x40);
    this->sendCommand(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
    this->sendCommand(SSD1306_NORMALDISPLAY);                 // 0xA6
    this->sendCommand(SSD1306_DISPLAYON);                     // 0xAF
    return 0;
}

void SSD1306::pushDisplay(void) {
    unsigned char page[17] = { 0x40 };
    unsigned int x, ii, count = this->getWidth() * this->getHeight() / 8;

    this->sendCommand(SSD1306_SETLOWCOLUMN | 0x0);  // low col = 0
    this->sendCommand(SSD1306_SETHIGHCOLUMN | 0x0);  // hi col = 0
    this->sendCommand(SSD1306_SETSTARTLINE | 0x0); // line #0
    for (ii = 0; ii < count; ii++) {
        // send a bunch of data in one xmission
        for (x = 1; x <= 16; x++) {
            page[x] = buffer[ii];
            ii++;
        }
        if (write(_i2cFileHandler, page, sizeof(page)) != sizeof(page)) {
            printf("problem with page %d\n", ii);
        }
        ii--;
    }
}

uint8_t SSD1306::getWidth() {
    uint8_t width = 0;

    switch(_type) {
        case SSD1306_128_64:
            width = 128;
            break;
        case SSD1306_128_32:
            width = 128;
            break;
        case SSD1306_96_16:
            width = 96;
            break;
    }
    return width;
}

uint8_t SSD1306::getHeight() {
    uint8_t height = 0;

    switch(_type) {
        case SSD1306_128_64:
            height = 64;
            break;
        case SSD1306_128_32:
            height = 32;
            break;
        case SSD1306_96_16:
            height = 16;
            break;
    }
    return height;
}
