#ifndef _PROGRESS_BAR_H
#define _PROGRESS_BAR_H

#include "Control.h"

class ProgressBar : public Control {
private:
    uint16_t m_progress = 0;     // How many pixels of progress to paint
    uint16_t m_lastProgress = 0; // How many pixels of progress we painted last time
    uint32_t m_progressX;        // Where to paint the bar to (absolute co-ordinate)
    uint16_t m_fillColor = TFT_BLUE;
    uint16_t m_borderColor = TFT_WHITE;
    uint16_t m_backgroundColor = TFT_BLACK;
    char myText[20];

public:
    void setProgress(uint32_t progress, uint32_t total);
    void show();
    void update();

    uint16_t getFillColor() { return m_fillColor; }
    void setFillColor(uint16_t c) { m_fillColor = c; }

    uint16_t getBorderColor() { return m_borderColor; }
    void setBorderColor(uint16_t c) { m_borderColor = c; }

    uint16_t getBackgroundColor() { return m_backgroundColor; }
    void setBackgroundColor(uint16_t c) { m_backgroundColor = c; }

    void before_paintText();
};

#endif // #ifndef _PROGRESS_BAR_H