#ifndef _BASICLOG_H
#define _BASICLOG_H

#include "PrintExt.h"

enum LogLevel
{
  LOG_ERR = 0,
  LOG_LOG = 1,
  LOG_DBG = 2,
  LOG_DBG2 = 3,
  LOG_DBG3 = 4
};

class BasicLog
{
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

private:
  PrintExt *m_dest;
  LogLevel m_logLvl = LOG_LOG;
  bool m_useLogLabels = true;
};

#endif // #ifndef _BASICLOG_H