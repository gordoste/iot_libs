#ifndef _EXTENDEDSERIAL_H
#define _EXTENDEDSERIAL_H

#include "PrintExt.h"
#include "StringUtils.h"

#ifdef OTA_ENABLED
#define MAX_OTA_WAIT 500
#include "JeVe_EasyOTA.h"
#endif

class ExtendedSerial : public PrintExt {
public:
    ExtendedSerial(){};
    void begin(int speed);
    virtual size_t write(uint8_t ch);

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