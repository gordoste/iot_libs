#include "BasicLog.h"

void BasicLog::begin(PrintExt *p)
{
    m_dest = p;
}

void BasicLog::useLogLabels(bool enable)
{
    m_useLogLabels = enable;
}

void BasicLog::setLogLevel(LogLevel lvl)
{
    m_logLvl = lvl;
}

void BasicLog::debug3(const char *fmt, ...)
{
    if (m_logLvl < LOG_DBG3)
        return;
    va_list argp;
    va_start(argp, fmt);
    if (m_useLogLabels)
        m_dest->print("DBG ");
    m_dest->vprintf(fmt, argp);
    va_end(argp);
}

void BasicLog::debug2(const char *fmt, ...)
{
    if (m_logLvl < LOG_DBG2)
        return;
    va_list argp;
    va_start(argp, fmt);
    if (m_useLogLabels)
        m_dest->print("DBG ");
    m_dest->vprintf(fmt, argp);
    va_end(argp);
}

void BasicLog::debug(const char *fmt, ...)
{
    if (m_logLvl < LOG_DBG)
        return;
    va_list argp;
    va_start(argp, fmt);
    if (m_useLogLabels)
        m_dest->print("DBG ");
    m_dest->vprintf(fmt, argp);
    va_end(argp);
}

void BasicLog::log(const char *fmt, ...)
{
    if (m_logLvl < LOG_LOG)
        return;
    va_list argp;
    va_start(argp, fmt);
    if (m_useLogLabels)
        m_dest->print("LOG ");
    m_dest->vprintf(fmt, argp);
    va_end(argp);
}

void BasicLog::error(const char *fmt, ...)
{
    if (m_logLvl < LOG_ERR)
        return;
    va_list argp;
    va_start(argp, fmt);
    if (m_useLogLabels)
        m_dest->print("ERR ");
    m_dest->vprintf(fmt, argp);
    va_end(argp);
}