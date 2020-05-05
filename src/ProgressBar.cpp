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