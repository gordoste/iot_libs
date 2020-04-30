#include "PrintExt.h"

void PrintExt::vprintf(const char *fmt, va_list argp) {
    vsnprintf(m_buf, sizeof(m_buf), fmt, argp);
    for (char *p = &m_buf[0]; *p; p++) // emulate cooked mode for newlines
    {
        if (*p == '\n')
            write('\r');
        write(*p);
    }
    autoNewline();
}

void PrintExt::printf(const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    vprintf(fmt, argp);
    va_end(argp);
}

#ifdef F // check to see if F() macro is available
void PrintExt::printf(const __FlashStringHelper *fmt, ...) {
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

bool PrintExt::getAutoNewline() {
    return m_autoNewline;
}

void PrintExt::setAutoNewline(bool autoNewline) {
    this->m_autoNewline = autoNewline;
}

void PrintExt::autoNewline() {
    if (!m_autoNewline)
        return;
    write('\r');
    write('\n');
}