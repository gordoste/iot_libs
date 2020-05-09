#include "Button.h"

void Button::init() {
    m_borderProps = { TFT_WHITE, 1 };
}

void Button::show() {
    clear();
    m_shown = true;
    paintBorder();
    paintText(); // Necessary to initialise m_textWin
    update();
}

void Button::update() {
    if (!m_shown) return;
    paintText();
}

void Button::before_paintText() {
    m_tft->fillRect(m_textWin.x, m_textWin.y, m_textWin.width, m_textWin.height, m_backgroundColor);
}
