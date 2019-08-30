#ifndef _SSD1306_CONSOLE_H
#define _EXTENDEDSERIAL_H

#include "PrintExt.h"
#include "StringUtils.h"

class ExtendedSerial : public PrintExt
{
public:
  ExtendedSerial(){};
  void begin(int speed);
  virtual size_t write(uint8_t ch);
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EXTENDEDSERIAL)
extern ExtendedSerial SerialExt;
#endif

#endif // #ifndef _SSD1306_CONSOLE_H