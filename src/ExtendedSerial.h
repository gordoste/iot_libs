#ifndef _EXTENDEDSERIAL_H
#define _EXTENDEDSERIAL_H

#include "PrintExt.h"
#include "StringUtils.h"

#ifndef SERIAL_PRINTF_BUF
#define SERIAL_PRINTF_BUF 80 // define the tmp buffer size (override via compiler flag)
#endif

#ifdef OTA_ENABLED
#define MAX_OTA_WAIT 500
#include "JeVe_EasyOTA.h"
#endif

class ExtendedSerial : public Stream {
public:
    ExtendedSerial() {};
    void begin(int speed);
    virtual size_t write(uint8_t ch);
    virtual int available();
    virtual int read();
    virtual int peek();
    virtual void flush();

    int getWriteError() { return Stream::getWriteError(); }
    void clearWriteError() { Stream::clearWriteError(); }

    void vprintf(const char *fmt, va_list argp);
    void printf(const char *fmt, ...);
#ifdef F // check to see if F() macro is available
    void printf(const __FlashStringHelper *fmt, ...);
#endif
    bool getAutoNewline() { return m_autoNewline; }
    void setAutoNewline(bool autoNewline) { m_autoNewline = autoNewline; };


#ifdef OTA_ENABLED
    void setOTA(EasyOTA *ota);
    char timedRead();

private:
    EasyOTA *m_ota;
    char m_buf[SERIAL_PRINTF_BUF];
    bool m_autoNewline = true;
    void autoNewline();

#endif
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EXTENDEDSERIAL)
extern ExtendedSerial SerialExt;
#endif

#endif // #ifndef _EXTENDEDSERIAL_H