#ifndef _BUTTON_H
#define _BUTTON_H

#include "TouchControl.h"

class Button : public TouchControl {
private:
    uint16_t m_fillColor = TFT_BLUE;
    uint16_t m_borderColor = TFT_WHITE;

public:
    void show();
    void update();

    uint16_t getFillColor() { return m_fillColor; }
    void setFillColor(uint16_t c) { m_fillColor = c; }

    uint16_t getBorderColor() { return m_borderColor; }
    void setBorderColor(uint16_t c) { m_borderColor = c; }

    void before_paintText();
};

#endif // #ifndef _BUTTON_H