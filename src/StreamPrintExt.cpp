#include "StreamPrintExt.h"

void StreamPrintExt::begin(Stream *str) { m_str = str; }

size_t StreamPrintExt::write(uint8_t ch) { return m_str->write(ch); }

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_STREAMPRINTEXT)
StreamPrintExt StreamExt;
#endif

