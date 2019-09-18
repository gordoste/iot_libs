#ifndef _STREAMPRINTEXT_H
#define _STREAMPRINTEXT_H

#include "PrintExt.h"

class StreamPrintExt : public PrintExt
{
public:
  StreamPrintExt(){};
  void begin(Stream *str);
  virtual size_t write(uint8_t ch);
  void setFlushOnNewline(bool flushOnNL);
private:
  Stream *m_str;
  bool m_flushOnNL = false;
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_STREAMPRINTEXT)
extern StreamPrintExt StreamExt;
#endif

#endif // #ifndef _STREAMPRINTEXT_H

