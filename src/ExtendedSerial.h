#ifndef _EXTENDEDSERIAL_H
#define _EXTENDEDSERIAL_H

#include "PrintExt.h"
#include "StringUtils.h"

class ExtendedSerial : public PrintExt
{
public:
  ExtendedSerial(){};
  void begin(int speed);
  virtual size_t write(uint8_t ch);
  uint16_t readLineWithEcho(char *buf, uint16_t bufLen, char (*readChar)() = NULL);
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EXTENDEDSERIAL)
extern ExtendedSerial SerialExt;
#endif

#endif // #ifndef _EXTENDEDSERIAL_H