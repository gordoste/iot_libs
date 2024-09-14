#include "ExtendedSerial.h"

void ExtendedSerial::begin(int speed) {
    Serial.begin(speed);
}

size_t ExtendedSerial::write(uint8_t ch) {
    ch = StringUtils::utf8ascii(ch);
    if (ch == 0) return 0;
    Serial.write(ch);
    if (ch == '\n') {
        Serial.flush();
    }
    return 1; // Processed 1 character
}

int ExtendedSerial::available() {
    return Serial.available();
}

int ExtendedSerial::read() {
    return Serial.read();
}

int ExtendedSerial::peek() {
    return Serial.peek();
}

void ExtendedSerial::flush() {
    Serial.flush();
}

void ExtendedSerial::vprintf(const char *fmt, va_list argp) {
    vsnprintf(m_buf, sizeof(m_buf), fmt, argp);
    for (char *p = &m_buf[0]; *p; p++) // emulate cooked mode for newlines
    {
        if (*p == '\n')
            write('\r');
        write(*p);
    }
    autoNewline();
}

void ExtendedSerial::printf(const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    vprintf(fmt, argp);
    va_end(argp);
}

#ifdef F // check to see if F() macro is available
void ExtendedSerial::printf(const __FlashStringHelper *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
#ifdef __AVR__
    vsnprintf_P(m_buf, sizeof(m_buf), (const char *)fmt, argp); // progmem for AVR
    for (char *p = &m_buf[0]; *p; p++)                          // emulate cooked mode for newlines
    {
        if (*p == '\n')
            write('\r');
        write(*p);
    }
#else
    vprintf((const char *)fmt, argp); // for the rest of the world
#endif
    va_end(argp);
    autoNewline();
}
#endif // #ifdef F

void ExtendedSerial::autoNewline() {
    if (!m_autoNewline)
        return;
    write('\r');
    write('\n');
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EXTENDEDSERIAL)
ExtendedSerial SerialExt;
#endif