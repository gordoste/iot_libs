#include "StreamPrintExt.h"

void StreamPrintExt::setStream(Stream *str) { m_str = str; }

size_t StreamPrintExt::write(uint8_t ch) {
    if (m_str == NULL) return 0;
    if (m_flushOnNL && ch == '\n') m_str->flush();
    return m_str->write(ch);
}

void StreamPrintExt::setFlushOnNewline(bool flushOnNL) {
    this->m_flushOnNL = flushOnNL;
}
