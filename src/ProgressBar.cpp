#include "ProgressBar.h"

void ProgressBar::setProgress(uint16_t progress, uint16_t total) {
    while (total < 0x8000U) { progress <<= 1; total <<= 1; } // Scale up to make math easier
    uint16_t step = total / (m_win->width-2); // Figure out value of one pixel
    m_progress = progress/step;
    update();
}

void ProgressBar::show() {
    TFTUtils::fillWindow(m_tft, *m_win, m_backgroundColor);
    m_tft->drawRect(m_win->x, m_win->y, m_win->width, m_win->height, m_borderColor);
    update();
    m_shown = true;
}

void ProgressBar::update() {
    if (m_progress != m_lastProgress) {
        m_tft->fillRect(m_win->x+1, m_win->y+1, m_progress, m_win->height-2, m_fillColor);
    }
    m_lastProgress = m_progress;
}