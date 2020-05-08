#include "Button.h"

void Button::show() {
    TFTUtils::fillWindow(m_tft, *m_win, m_backgroundColor);
    m_tft->drawRect(m_win->x, m_win->y, m_win->width, m_win->height, m_borderColor);
    m_shown = true;
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
