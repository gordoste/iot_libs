#include "Control.h"

Control &Control::init(TFT_eSPI *tft, Window *win) {
    m_tft = tft;
    m_win = win;
    return *this;
}

#ifdef LOAD_GFXFF

Control &Control::setFreeFont(const GFXfont *f) {
    if (f == nullptr) return setTextFont(1);
    m_textFont = 1;
    m_gfxFont = (GFXfont *)f;
    return *this;
}

Control &Control::setTextFont(uint8_t f) {
    m_textFont = (f > 0) ? f : 1; // Don't allow font 0
    m_gfxFont = NULL;
    return *this;
}

#else
// Alternative to setTextFont() so we don't need two different named functions
Control &Control::setFreeFont(uint8_t font) {
    return setTextFont(font);
}

Control &Control::setTextFont(uint8_t f) {
    textfont = (f > 0) ? f : 1; // Don't allow font 0
    return *this;
}
#endif

void Control::updateTFTFont() {
    if (m_gfxFont != NULL) {
        m_tft->setFreeFont(m_gfxFont);
    } else {
        m_tft->setTextFont(m_textFont);
    }
    m_tft->setTextColor(m_textColor);
}

Control &Control::setText(const char *str) {
    updateTFTFont();
    m_text = str;
    showText(m_text);
    return *this;
}

void Control::showText(const char *str) {
    Point textPos = {0, 0};
    // Calculate where the text should be
    switch (m_textAlign) {
    case TL_DATUM:
    case ML_DATUM:
    case BL_DATUM:
        textPos.x = m_win->x + m_textPadding;
        break;
    case TC_DATUM:
    case MC_DATUM:
    case BC_DATUM:
        textPos.x = m_win->x + (m_win->width / 2);
        break;
    case TR_DATUM:
    case MR_DATUM:
    case BR_DATUM:
        textPos.x = m_win->x + m_win->width - m_textPadding;
        break;
    default:
        textPos.x = m_win->x;
    }
    switch (m_textAlign) {
    case TL_DATUM:
    case TC_DATUM:
    case TR_DATUM:
        textPos.y = m_win->y + m_textPadding;
        break;
    case ML_DATUM:
    case MC_DATUM:
    case MR_DATUM:
        textPos.y = m_win->y + (m_win->height / 2);
        break;
    case BL_DATUM:
    case BC_DATUM:
    case BR_DATUM:
        textPos.y = m_win->y + m_win->height - m_textPadding;
        break;
    default:
        textPos.y = m_win->y;
    }
    m_tft->setTextDatum(m_textAlign);
    m_textWin.width = m_tft->drawString(str, textPos.x, textPos.y);
    m_textWin.height = m_tft->fontHeight();
    // Update textWindow with actual positions from TFT library
    switch (m_textAlign) {
    case TL_DATUM:
    case ML_DATUM:
    case BL_DATUM:
        m_textWin.x = textPos.x;
        break;
    case TC_DATUM:
    case MC_DATUM:
    case BC_DATUM:
        m_textWin.x = textPos.x - (m_textWin.width / 2);
        break;
    case TR_DATUM:
    case MR_DATUM:
    case BR_DATUM:
        m_textWin.x = textPos.x - m_textWin.width;
        break;
    default:
        m_textWin.x = textPos.y;
    }
    switch (m_textAlign) {
    case TL_DATUM:
    case TC_DATUM:
    case TR_DATUM:
        m_textWin.y = textPos.y;
        break;
    case ML_DATUM:
    case MC_DATUM:
    case MR_DATUM:
        m_textWin.y = textPos.y - (m_textWin.height / 2);
        break;
    case BL_DATUM:
    case BC_DATUM:
    case BR_DATUM:
        m_textWin.y = textPos.y - m_textWin.height;
        break;
    default:
        m_textWin.y = textPos.y;
    }
}