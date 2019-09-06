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

uint16_t ExtendedSerial::readLineWithEcho(char *buf, uint16_t bufLen, char (*readChar)() /* = NULL */) {
  uint16_t read = 0;
  while (read < bufLen) {
    buf[read] = (readChar == NULL ? Serial.read() : (*readChar)());
    if (buf[read] != '\r') Serial.write(buf[read]);
    if (buf[read] == '\n') {
      buf[read] = '\0';
      return read;
    }
    read++;
  }
  return read;
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EXTENDEDSERIAL)
ExtendedSerial SerialExt;
#endif