#ifndef _SSD1306_CONSOLE_H
#define _SSD1306_CONSOLE_H

#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#include "PrintExt.h"

class SSD1306Console : public PrintExt {
public:
    SSD1306Console(){};
    void begin(uint8_t i2cAddress);
    void begin(uint8_t i2cAddress, uint8_t dtaPin, uint8_t clkPin);
    uint8_t displayWidth();
    // printf() which blanks the rest of the line
    void printfln(const char *fmt, ...);
    virtual size_t write(uint8_t ch);

private:
    int m_chPos = 0;
    SSD1306AsciiWire m_oled;
    uint8_t m_displayWidth;
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_CONSOLE)
extern SSD1306Console Console;
#endif

#endif // #ifndef _SSD1306_CONSOLE_H