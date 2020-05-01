#include "Control.h"

void Control::init(TFT_eSPI *tft, Window *win) {
    m_tft = tft;
    m_win = win;
}
