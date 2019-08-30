#include "ExtendedSerial.h"

// ****** UTF8-Decoder: convert UTF8-string to extended ASCII *******
static uint8_t c1;  // Last character buffer

// Convert a single Character from UTF8 to Extended ASCII
// Return "0" if a byte has to be ignored
uint8_t utf8ascii(uint8_t ascii) {
  if (ascii < 128) {   // Standard ASCII-set 0..0x7F handling
    c1 = 0;
    return ascii;
  }

  // get previous input
  uint8_t last = c1;   // get last char
  c1 = ascii;         // remember actual character

  switch (last) {   // conversion depending on first UTF8-character
    case 0xC2: return ascii; break;
    case 0xC3: return (ascii | 0xC0); break;
    case 0x82: if (ascii==0xAC) return 0x80;       // special case Euro-symbol
  }

  return 0;                                     // otherwise: return zero, if character has to be ignored
}

void ExtendedSerial::begin(int speed)
{
    Serial.begin(speed);
}

size_t ExtendedSerial::write(uint8_t ch)
{
    ch = utf8ascii(ch);
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