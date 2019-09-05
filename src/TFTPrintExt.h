#ifndef _TFTPRINTEXT_H
#define _TFTPRINTEXT_H

#include "PrintExt.h"
#include "TFT_eSPI.h"

class TFTPrintExt : public PrintExt
{
public:
  TFTPrintExt(){};
  void begin(TFT_eSPI *tft);
  virtual size_t write(uint8_t ch);
private:
  TFT_eSPI *m_tft;
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EXTENDEDSERIAL)
extern TFTPrintExt TFTExt;
#endif

#endif // #ifndef _TFTPRINTEXT_H