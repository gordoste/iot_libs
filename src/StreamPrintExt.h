#ifndef _STREAMPRINTEXT_H
#define _STREAMPRINTEXT_H

#include "PrintExt.h"

class StreamPrintExt : public PrintExt {
public:
    StreamPrintExt(){};
    void setStream(Stream *str);
    virtual size_t write(uint8_t ch);
    void setFlushOnNewline(bool flushOnNL);
    void printfln(const char *fmt, ...);

private:
    Stream *m_str = NULL;
    bool m_flushOnNL = false;
};

#endif // #ifndef _STREAMPRINTEXT_H
