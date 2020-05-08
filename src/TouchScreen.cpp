#include "TouchScreen.h"

void TouchScreen::init(BasicLog *log, TFT_eSPI *tft) {
    m_log = log;
    m_tft = tft;
}

void TouchScreen::addControl(Control *ctl, Window *win) {
    ctl->init(m_log, m_tft, win);
    m_listOfControls.push_back(ctl);
}

void TouchScreen::addTouchControl(TouchControl *ctl, Window *win) {
    m_listOfTouchControls.push_back(ctl);
    addControl(ctl, win);
}

TouchControl *TouchScreen::checkForTouch() {
    if (m_tft->getTouch(&m_touchX, &m_touchY)) {
        std::list<TouchControl *>::iterator it = m_listOfTouchControls.begin();
        while (it != m_listOfTouchControls.end()) {
            Window *ctlWin = (*it)->getWindow();
            if (TFTUtils::contains((*ctlWin), m_touchX, m_touchY)) {
                (*it)->handleTouch(m_touchX, m_touchY, true);
                return (*it);
            }
            it++;
        }
    }
    return NULL;
}
