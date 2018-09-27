#include "SSD1306Console.h"

void SSD1306Console::begin(uint8_t i2cAddress)
{
    m_oled.begin(&Adafruit128x64, 0x3C);
    m_oled.setFont(lcd5x7);
    m_displayWidth = m_oled.displayWidth() / (m_oled.fontWidth() + m_oled.letterSpacing());
#ifdef INCLUDE_SCROLLING
    m_oled.setScrollMode(SCROLL_MODE_AUTO);
#endif
    m_oled.clear();
}

void SSD1306Console::begin(uint8_t i2cAddress, uint8_t dtaPin, uint8_t clkPin)
{
    Wire.begin(dtaPin, clkPin);
    begin(i2cAddress);
}

void SSD1306Console::printfln(const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    bool nlStore = getAutoNewline();
    setAutoNewline(false);
    vprintf(fmt, argp);
    m_oled.clearToEOL();
    setAutoNewline(nlStore);
    va_end(argp);
}

uint8_t SSD1306Console::displayWidth()
{
    return m_displayWidth;
}

size_t SSD1306Console::write(uint8_t ch)
{ // Grabs character from print
    if (m_chPos >= m_displayWidth || char(ch) == '\n')
    { /// auto line splitting if line is bigger than display
        m_chPos = 0;
        m_oled.print('\n');
    }
    if (char(ch) != '\n')
    {
        m_oled.print(char(ch));
        if (char(ch) == '\r') {
            m_chPos=0;
        }
        else {
            m_chPos++;
        }
    }
    return 1; // Processed 1 character
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SSD1306CONSOLE)
SSD1306Console Console;
#endif