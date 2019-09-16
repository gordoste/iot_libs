#include "TFTPrintExt.h"

#ifdef TFT_ENABLED

void TFTPrintExt::begin(TFT_eSPI *tft, Window *win)
{
    m_tft = tft;
    m_win = win;
    if (m_win == NULL) { m_cursor = { 0, 0 }; }
    else { m_cursor = { m_win->x, m_win->y }; }
}

void TFTPrintExt::clear() {
    TFTUtils::fillWindow(m_tft, *m_win, TFT_BLACK);
    if (m_win == NULL) m_tft->setCursor(0, 0);
    else m_tft->setCursor(m_win->x, m_win->y);
    m_cursor = { m_tft->getCursorX(), m_tft->getCursorY() };
}

size_t TFTPrintExt::write(uint8_t ch)
{
    if (ch == 0) return 0;
    if (ch == '\r') {
        m_tft->setCursor(0, m_cursor.y);
    }
    else {
        m_tft->setCursor(m_cursor.x, m_cursor.y);
        m_tft->setTextFont(1);
        m_tft->setTextColor(TFT_WHITE);
        m_tft->write(ch);
        if (m_tft->getCursorY() >= m_tft->height()) clear();   
        m_cursor = { m_tft->getCursorX(), m_tft->getCursorY() };
    }
    return 1; // Processed 1 character
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_EXTENDEDSERIAL)
TFTPrintExt TFTExt;
#endif

#endif