#include "ExtendedSerial.h"

void ExtendedSerial::begin(int speed)
{
    Serial.begin(speed);
}

size_t ExtendedSerial::write(uint8_t ch)
{
    ch = StringUtils::utf8ascii(ch);
    if (ch == 0) return 0;
    Serial.write(ch);
    if (ch == '\n') {
        Serial.flush();
    }
    return 1; // Processed 1 character
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EXTENDEDSERIAL)
ExtendedSerial SerialExt;
#endif