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
    // int getWriteError()
    // {
    //     return write_error;
    // }
    // void clearWriteError()
    // {
    //     setWriteError(0);
    // }

    // size_t printf(const char * format, ...)  __attribute__ ((format (printf, 2, 3)));
    // size_t print(const __FlashStringHelper *);
    // size_t print(const String &);
    // size_t print(const char[]);
    // size_t print(char);
    // size_t print(unsigned char, int = DEC);
    // size_t print(int, int = DEC);
    // size_t print(unsigned int, int = DEC);
    // size_t print(long, int = DEC);
    // size_t print(unsigned long, int = DEC);
    // size_t print(double, int = 2);
    // size_t print(const Printable&);
    // size_t print(struct tm * timeinfo, const char * format = NULL);

    // size_t println(const __FlashStringHelper *);
    // size_t println(const String &s);
    size_t println(const char[]);
    // size_t println(char);
    // size_t println(unsigned char, int = DEC);
    // size_t println(int, int = DEC);
    // size_t println(unsigned int, int = DEC);
    // size_t println(long, int = DEC);
    // size_t println(unsigned long, int = DEC);
    // size_t println(double, int = 2);
    // size_t println(const Printable&);
    // size_t println(struct tm * timeinfo, const char * format = NULL);
    // size_t println(void);
    

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