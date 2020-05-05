#ifndef _CONTROL_H
#define _CONTROL_H

#include "TFTUtils.h"

class Control {
protected:
    TFT_eSPI *m_tft;
    Window *m_win;
    bool m_shown = false;
    uint8_t m_textFont = 1;
    uint8_t m_textAlign = TL_DATUM;
    uint8_t m_textPadding = 0;
    uint16_t m_textColor = TFT_WHITE;
    uint16_t m_textWidth = 0;
    Window m_textWin = { 0, 0, 0, 0 }; // Area the text takes up
    const char *m_text;
#ifdef LOAD_GFXFF
    GFXfont *m_gfxFont = NULL;
#endif

public:
    Control &init(TFT_eSPI *tft, Window *win);
    Window *getWindow() { return m_win; }
    virtual void show() = 0; // Pure virtual function that needs to be implemented in child
    virtual void update() { show(); } // Can be over-ridden
    Control &setText(const char *str);
    Control &setTextAlign(uint8_t textAlign) {
        m_textAlign = textAlign;
        return *this;
    }
    uint8_t getTextAlign() { return m_textAlign; }
    Control &setTextColor(uint16_t color) {
        m_textColor = color;
        return *this;
    }
    uint16_t getTextColor() { return m_textColor; }
    Control &setTextPadding(uint8_t textPadding) {
        m_textPadding = textPadding;
        return *this;
    }
    uint8_t getTextPadding() { return m_textPadding; }

#ifdef LOAD_GFXFF
    Control &setFreeFont(const GFXfont *f = NULL);
    Control &setTextFont(uint8_t font);
#else
    Control &setFreeFont(uint8_t font);
    Control &setTextFont(uint8_t font);
#endif

protected:
    void updateTFTFont(); // Set the font on the TFT before drawing text
    virtual void showText(const char *str); // Display text. Can be over-ridden
};

#endif // #ifndef _CONTROL_H
