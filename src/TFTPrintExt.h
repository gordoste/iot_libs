#ifndef _TFTPRINTEXT_H
#define _TFTPRINTEXT_H

#ifdef TFT_ENABLED

#include "PrintExt.h"
#include "TFT_eSPI.h"
#include "TFTUtils.h"

class TFTPrintExt : public PrintExt
{
  public:
    TFTPrintExt(){};
    void begin(TFT_eSPI *tft, Window *win = NULL);
    void clear();
    virtual size_t write(uint8_t ch);
  private:
    TFT_eSPI *m_tft;
    Window *m_win;
    Point m_cursor;
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EXTENDEDSERIAL)
extern TFTPrintExt TFTExt;
#endif

#endif // #ifdef TFT_ENABLED

#endif // #ifndef _TFTPRINTEXT_H

