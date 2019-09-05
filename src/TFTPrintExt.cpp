#include "TFTPrintExt.h"

void TFTPrintExt::begin(TFT_eSPI *tft)
{
    m_tft = tft;
}

size_t TFTPrintExt::write(uint8_t ch)
{
    if (ch == 0) return 0;
    m_tft->write(ch);
    return 1; // Processed 1 character
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EXTENDEDSERIAL)
TFTPrintExt TFTExt;
#endif