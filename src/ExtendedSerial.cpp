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

size_t ExtendedSerial::println(const char c[]) { return Stream::println(c); }

#ifdef OTA_ENABLED
void ExtendedSerial::setOTA(EasyOTA *ota) { m_ota = ota; }

char ExtendedSerial::timedRead() {
    unsigned long lastOTA = 0;
    while (!Serial.available()) {
        if (millis() - lastOTA > MAX_OTA_WAIT) {
            m_ota->loop();
            lastOTA = millis();
        }
    }
    return Serial.read();
}
#endif

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EXTENDEDSERIAL)
ExtendedSerial SerialExt;
#endif