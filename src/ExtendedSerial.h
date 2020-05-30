#ifndef _EXTENDEDSERIAL_H
#define _EXTENDEDSERIAL_H

#include "PrintExt.h"
#include "StringUtils.h"

#ifdef OTA_ENABLED
#define MAX_OTA_WAIT 500
#include "JeVe_EasyOTA.h"
#endif

class ExtendedSerial : public PrintExt, public Stream {
public:
    ExtendedSerial(){};
    void begin(int speed);
    virtual size_t write(uint8_t ch);
    virtual int available();
    virtual int read();
    virtual int peek();
    virtual void flush();

    int getWriteError() { return Stream::getWriteError(); }
    void clearWriteError() { Stream::clearWriteError(); }

    size_t print(const __FlashStringHelper *s) { return Stream::print(s); };
    size_t print(const String &s) { return Stream::print(s); };
    size_t print(const char c[]) { return Stream::print(c); };
    size_t print(char c) { return Stream::print(c); };
    size_t print(unsigned char c, int b = DEC) { return Stream::print(c, b); };
    size_t print(int i, int b = DEC) { return Stream::print(i, b); };
    size_t print(unsigned int i, int b = DEC) { return Stream::print(i, b); };
    size_t print(long l, int b = DEC) { return Stream::print(l, b); };
    size_t print(unsigned long l, int b = DEC) { return Stream::print(l, b); };
    size_t print(double d, int b = 2) { return Stream::print(d, b); };
    size_t print(const Printable& s) { return Stream::print(s); };
    size_t print(struct tm * timeinfo, const char * format = NULL) { return Stream::print(timeinfo, format); };

    size_t println(const __FlashStringHelper *s) { return Stream::println(s); };
    size_t println(const String &s) { return Stream::println(s); };
    size_t println(const char c[]) { return Stream::println(c); };
    size_t println(char c) { return Stream::println(c); };
    size_t println(unsigned char c, int b = DEC) { return Stream::println(c, b); };
    size_t println(int i, int b = DEC) { return Stream::println(i, b); };
    size_t println(unsigned int i, int b = DEC) { return Stream::println(i, b); };
    size_t println(long l, int b = DEC) { return Stream::println(l, b); };
    size_t println(unsigned long l, int b = DEC) { return Stream::println(l, b); };
    size_t println(double d, int b = 2) { return Stream::println(d, b); };
    size_t println(const Printable& s) { return Stream::println(s); };
    size_t println(struct tm * timeinfo, const char * format = NULL) { return Stream::println(timeinfo, format); };
    size_t println(void) { return Stream::println(); };
    

#ifdef OTA_ENABLED
    void setOTA(EasyOTA *ota);
    char timedRead();

private:
    EasyOTA *m_ota;
#endif
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EXTENDEDSERIAL)
extern ExtendedSerial SerialExt;
#endif

#endif // #ifndef _EXTENDEDSERIAL_H