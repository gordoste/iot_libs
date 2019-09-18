#include "StreamPrintExt.h"

void StreamPrintExt::begin(Stream *str) { m_str = str; }

size_t StreamPrintExt::write(uint8_t ch) {
    if (m_flushOnNL && ch == '\n') m_str->flush();
    return m_str->write(ch);
}

void StreamPrintExt::setFlushOnNewline(bool flushOnNL) {
    this->m_flushOnNL = flushOnNL;
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_STREAMPRINTEXT)
StreamPrintExt StreamExt;
#endif

