#include "Label.h"

void Label::init() {
    m_borderProps = { TFT_WHITE, 1 };
}

void Label::show() {
    clear();
    m_shown = true;
    paintBorder();
    paintFill();
    paintText(); // Necessary to initialise m_textWin
    update();
}

void Label::update() {
    if (!m_shown) return;
    paintFill();
    paintText();
}