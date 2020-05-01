#ifndef _CONTROL_H
#define _CONTROL_H

#include "TFTUtils.h"

class Control {
protected:
    TFT_eSPI *m_tft;
    Window *m_win;
    bool m_shown = false;
public:
    void init(TFT_eSPI *tft, Window *win);
    Window *getWindow() { return m_win; }
    virtual void show() = 0;
    virtual void update() { show(); }
};

#endif // #ifndef _CONTROL_H
