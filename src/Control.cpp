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
