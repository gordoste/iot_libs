#ifndef _BASICLOG_H
#define _BASICLOG_H

#include "PrintExt.h"

enum LogLevel {
    LOG_ERR = 0,
    LOG_LOG = 1,
    LOG_DBG = 2,
    LOG_DBG2 = 3,
    LOG_DBG3 = 4
};

class BasicLog {
public:
    BasicLog(){};
    void begin(PrintExt *p);
    void setLogLevel(LogLevel lvl);
    void debug3(const char *fmt, ...);
    void debug2(const char *fmt, ...);
    void debug(const char *fmt, ...);
    void log(const char *fmt, ...);
    void error(const char *fmt, ...);
    void useLogLabels(bool enable);

#ifdef F // check to see if F() macro is available
    void debug3(const __FlashStringHelper *fmt, ...);
    void debug2(const __FlashStringHelper *fmt, ...);
    void debug(const __FlashStringHelper *fmt, ...);
    void log(const __FlashStringHelper *fmt, ...);
    void error(const __FlashStringHelper *fmt, ...);
#endif

private:
    PrintExt *m_dest;
    LogLevel m_logLvl = LOG_LOG;
    bool m_useLogLabels = true;
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_BASICLOG)
extern BasicLog Log;                                // Logging object
#endif

#endif // #ifndef _BASICLOG_H