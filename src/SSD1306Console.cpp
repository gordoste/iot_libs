#include "SSD1306Console.h"

void SSD1306Console::begin(uint8_t i2cAddress) {
    ota_prevLine = -1;
    ota_progress_millis = 0;
    memset(ota_progressBar, ' ', OTA_PROGRESS_BAR_SIZE);
    ota_progressBar[0] = '[';
    ota_progressBar[OTA_PROGRESS_BAR_SIZE - 1] = ']';
    ota_progressBar[OTA_PROGRESS_BAR_SIZE] = '\0';

    m_oled.begin(&Adafruit128x64, 0x3C);
    m_oled.setFont(lcd5x7);
    m_displayWidth = m_oled.displayWidth() / (m_oled.fontWidth() + m_oled.letterSpacing());
#ifdef INCLUDE_SCROLLING
    m_oled.setScrollMode(SCROLL_MODE_AUTO);
#endif
    m_oled.clear();
}

void SSD1306Console::begin(uint8_t i2cAddress, uint8_t dtaPin, uint8_t clkPin) {
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

uint8_t SSD1306Console::displayWidth() {
    return m_displayWidth;
}

size_t SSD1306Console::write(uint8_t ch) {               // Grabs character from print
    if (m_chPos >= m_displayWidth || char(ch) == '\n') { /// auto line splitting if line is bigger than display
        m_chPos = 0;
        m_oled.print('\n');
    }
    if (char(ch) != '\n') {
        m_oled.print(char(ch));
        if (char(ch) == '\r') {
            m_chPos = 0;
        } else {
            m_chPos++;
        }
    }
    return 1; // Processed 1 character
}

void SSD1306Console::showMessage(const String &message, int line) {
    setAutoNewline(false);
    // If line is same as last time, we want to overwrite the existing text
    if (line == ota_prevLine) {
        printfln("\r%s", message.c_str()); // printfln() blanks the rest of the line after printing
    } else {
        if (ota_prevLine >= 0) print("\n");
        print(message.c_str());
    }
    ota_prevLine = line;
    setAutoNewline(true);
}

void SSD1306Console::onElegantOTAStart() {
    showMessage("OTA starting...", 1);
}

void SSD1306Console::onElegantOTAProgress(size_t current, size_t final) {
    // Log every 1 second
    if (millis() - ota_progress_millis > 1000) {
        static unsigned int prevProg = 100;
        unsigned int prog = current / (final / (OTA_PROGRESS_BAR_SIZE - 2));
        if (prog != prevProg) {
            memset(ota_progressBar + sizeof(char), '=', prog);
            showMessage(ota_progressBar, 2);
        }
    }
}

void SSD1306Console::onElegantOTAEnd(bool success) {
    if (success) {
        showMessage("OTA done.Reboot...", 1); 
    } else {
        showMessage("OTA failed.", 1); 
    }
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_CONSOLE)
SSD1306Console Console;
#endif