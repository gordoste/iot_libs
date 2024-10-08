#include "BasicLog.h"

void BasicLog::begin(PrintExt *p) {
    dest = p;
}

void BasicLog::debug3(const char *fmt, ...) {
    if (level < LOG_DBG3)
        return;
    va_list argp;
    va_start(argp, fmt);
    if (useLabels)
        dest->print("DBG ");
    dest->vprintf(fmt, argp);
    va_end(argp);
}

void BasicLog::debug2(const char *fmt, ...) {
    if (level < LOG_DBG2)
        return;
    va_list argp;
    va_start(argp, fmt);
    if (useLabels)
        dest->print("DBG ");
    dest->vprintf(fmt, argp);
    va_end(argp);
}

void BasicLog::debug(const char *fmt, ...) {
    if (level < LOG_DBG)
        return;
    va_list argp;
    va_start(argp, fmt);
    if (useLabels)
        dest->print("DBG ");
    dest->vprintf(fmt, argp);
    va_end(argp);
}

void BasicLog::log(const char *fmt, ...) {
    if (level < LOG_LOG)
        return;
    va_list argp;
    va_start(argp, fmt);
    if (useLabels)
        dest->print("LOG ");
    dest->vprintf(fmt, argp);
    va_end(argp);
}

void BasicLog::error(const char *fmt, ...) {
    if (level < LOG_ERR)
        return;
    va_list argp;
    va_start(argp, fmt);
    if (useLabels)
        dest->print("ERR ");
    dest->vprintf(fmt, argp);
    va_end(argp);
}

#ifdef F // check to see if F() macro is available
void BasicLog::debug3(const __FlashStringHelper *fmt, ...) {
    if (level < LOG_DBG3)
        return;
    va_list argp;
    va_start(argp, fmt);
    strcpy_P(flashBuf, (PGM_P)fmt);
    if (useLabels)
        dest->print("DBG ");
    strcpy_P(flashBuf, (PGM_P)fmt);
    dest->vprintf(flashBuf, argp);
    va_end(argp);
}

void BasicLog::debug2(const __FlashStringHelper *fmt, ...) {
    if (level < LOG_DBG2)
        return;
    va_list argp;
    va_start(argp, fmt);
    if (useLabels)
        dest->print("DBG ");
    strcpy_P(flashBuf, (PGM_P)fmt);
    dest->vprintf(flashBuf, argp);
    va_end(argp);
}

void BasicLog::debug(const __FlashStringHelper *fmt, ...) {
    if (level < LOG_DBG)
        return;
    va_list argp;
    va_start(argp, fmt);
    if (useLabels)
        dest->print("DBG ");
    strcpy_P(flashBuf, (PGM_P)fmt);
    dest->vprintf(flashBuf, argp);
    va_end(argp);
}

void BasicLog::log(const __FlashStringHelper *fmt, ...) {
    if (level < LOG_LOG)
        return;
    va_list argp;
    va_start(argp, fmt);
    if (useLabels)
        dest->print("LOG ");
    strcpy_P(flashBuf, (PGM_P)fmt);
    dest->vprintf(flashBuf, argp);
    va_end(argp);
}

void BasicLog::error(const __FlashStringHelper *fmt, ...) {
    if (level < LOG_ERR)
        return;
    va_list argp;
    va_start(argp, fmt);
    if (useLabels)
        dest->print("ERR ");
    strcpy_P(flashBuf, (PGM_P)fmt);
    dest->vprintf(flashBuf, argp);
    va_end(argp);
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_BASICLOG)
BasicLog Log;                                // Logging object
#endif

#endif
