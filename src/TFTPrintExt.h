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
    Point &getCursor();
    void setFillColor(uint32_t fillColor);
    void setTextColor(uint32_t textColor);
    void onWrite(TFTHandler fn) { onWriteFn = fn; };
    virtual size_t write(uint8_t ch);
  private:
    TFT_eSPI *m_tft;
    Window *m_win;
    Point m_cursor;
    uint32_t m_fillColor = TFT_BLACK;
    uint32_t m_textColor = TFT_WHITE;
    TFTHandler onWriteFn = NULL;
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EXTENDEDSERIAL)
extern TFTPrintExt TFTExt;
#endif

#endif // #ifdef TFT_ENABLED

#endif // #ifndef _TFTPRINTEXT_H

