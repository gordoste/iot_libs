#ifndef _TOUCH_CONTROL_H
#define _TOUCH_CONTROL_H

#include "Control.h"

typedef std::function<void(uint16_t x, uint16_t y, bool absolute)> TouchHandler;

class TouchControl : public Control {
protected:
    TouchHandler m_touchHandler = TFTUtils::ignoreTouch;
    uint32_t m_lastTouchTime = 0;

public:
    void handleTouch(uint16_t x, uint16_t y, bool absolute);
};

#endif // #ifndef _TOUCH_CONTROL_H
