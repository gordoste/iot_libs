#include "TFTPrintExt.h"

void TFTPrintExt::begin(TFT_eSPI *tft)
{
    m_tft = tft;
}

size_t TFTPrintExt::write(uint8_t ch)
{
    if (ch == 0) return 0;
    if (ch == '\r') {
        m_tft->setCursor(0, m_tft->getCursorY());
        return 1;
    }
    m_tft->write(ch);
    if (m_tft->getCursorY() >= m_tft->height()) {
        m_tft->fillScreen(TFT_BLACK);
        m_tft->setCursor(0,0);
    }   
    return 1; // Processed 1 character
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EXTENDEDSERIAL)
TFTPrintExt TFTExt;
#endif