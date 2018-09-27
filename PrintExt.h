#ifndef _PRINTEXT_H
#define _PRINTEXT_H

#ifndef PRINTEXT_PRINTF_BUF
#define PRINTEXT_PRINTF_BUF 80 // define the tmp buffer size (override via compiler flag)
#endif

#include <Arduino.h>

// All methods add a newline if AutoNewline is enabled.
class PrintExt : public Print
{
public:
  void printf(const char *fmt, ...);
#ifdef F // check to see if F() macro is available
  void printf(const __FlashStringHelper *fmt, ...);
#endif
  // Use this to easily make similar functions
  void vprintf(const char *fmt, va_list argp);
  bool getAutoNewline();
  void setAutoNewline(bool autoNewline);
private:
  char m_buf[PRINTEXT_PRINTF_BUF];
  bool m_autoNewline = true;
  void autoNewline();
};

#endif // #ifndef _PRINTEXT_H