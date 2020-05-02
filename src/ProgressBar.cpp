#include "ProgressBar.h"

void ProgressBar::setProgress(uint32_t progress, uint32_t total) {
    while (total < 0x8000U) {
        progress <<= 1;
        total <<= 1;
    }                                           // Scale up to make math easier
    uint32_t step = total / (m_win->width - 2); // Figure out value of one pixel
    m_progress = progress / step;
    update();
}

void ProgressBar::show() {
    TFTUtils::fillWindow(m_tft, *m_win, m_backgroundColor);
    m_tft->drawRect(m_win->x, m_win->y, m_win->width, m_win->height, m_borderColor);
    update();
    m_shown = true;
}

void ProgressBar::showText(const char *str) {
    Point textPos = {0, 0};
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

void ProgressBar::update() {
    if (m_progress == m_lastProgress) return;
    Window fillWin;
    uint16_t fillColor = m_fillColor;
    fillWin.y = m_win->y + 1;
    fillWin.height = m_win->height - 2;
    if (m_progress > m_lastProgress) {
        fillWin.x = m_win->x + 1 + m_lastProgress;
        fillWin.width = m_progress - m_lastProgress;
        fillColor = m_fillColor;
    }
    if (m_progress < m_lastProgress) {
        fillWin.x = m_win->x + 1 + m_progress;
        fillWin.width = m_lastProgress - m_progress;
        fillColor = m_backgroundColor;
    }
    m_tft->fillRect(fillWin.x, fillWin.y, fillWin.width, fillWin.height, fillColor);
    if (TFTUtils::overlaps(m_textWin, fillWin)) setText(m_text);

    m_lastProgress = m_progress;
}