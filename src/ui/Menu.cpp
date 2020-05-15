#include "Menu.h"

Menu *Menu::setChoiceBorderProps(LineProperties &_props) {
    m_choiceBorderProps.color = _props.color;
    m_choiceBorderProps.width = _props.width;
    return this;
}

Menu *Menu::setSelectedBorderProps(LineProperties &_props) {
    m_selectedBorderProps.color = _props.color;
    m_selectedBorderProps.width = _props.width;
    return this;
}

Menu *Menu::setNumChoices(uint8_t _n, uint8_t _x, uint8_t _y) {
    m_numChoices = _n;
    m_xDivs = _x > 0 ? _x : 1;
    m_yDivs = _y > 0 ? _y : 1;
    m_divX = m_win->width / m_xDivs; // size of each cell
    m_divY = m_win->height / m_yDivs;
    m_shown = false;
    setSelectedChoice(-1);
    return this;
}

void Menu::show() {
    m_log->debug2("selectGrid() %d:%d:%d:%d:%d:%d", m_xDivs, m_yDivs, m_numChoices, m_selectedChoice);
    uint8_t cellNum;
    m_log->debug3("sG_begin-%d:%d:%d:%d", m_win->x, m_win->y, m_win->width, m_win->height);
    for (cellNum = 0; cellNum < m_numChoices; cellNum++)
        drawCell(cellNum);
    m_touchHandler = [this](uint16_t x, uint16_t y, bool absolute) {
        if (!absolute) { // handle relative co-ordinates
            x += m_win->x;
            y += m_win->y;
        }

        int8_t sel = -1;
        for (uint8_t t = 0; t < m_numChoices; t++) {
            getCell(t);
            if (TFTUtils::contains(m_currentCell, x, y)) {
                sel = t;
            }
        }
        setSelectedChoice(sel);
    };
    m_shown = true;
    m_log->debug2(F("selectGrid() leave"));
    return;
}

int8_t Menu::getSelectedChoice() { return m_selectedChoice; }
Menu *Menu::setSelectedChoice(int8_t _cellNum) {
    if (_cellNum == m_selectedChoice) return this;
    if (_cellNum >= m_numChoices) return this;
    int8_t oldSel = m_selectedChoice;
    m_selectedChoice = _cellNum;
    if (m_shown) {
        if (oldSel != -1) drawCell(oldSel);           // Redraw previously selected cell
        if (m_selectedChoice != -1) drawCell(m_selectedChoice); // Draw newly selected cell
    }
    return this;
};

void Menu::getCell(uint8_t c) {
    m_currentDiv[0] = c % m_xDivs;
    m_currentDiv[1] = c / m_xDivs;
    m_currentCell.x = m_win->x + m_currentDiv[0] * m_divX;
    m_currentCell.y = m_win->y + m_currentDiv[1] * m_divY;
    m_currentCell.width = m_currentDiv[0] == m_xDivs - 1 ? m_win->width - (m_divX * m_currentDiv[0]) : m_divX;   // if last cell in row, use remaining pixels
    m_currentCell.height = m_currentDiv[1] == m_yDivs - 1 ? m_win->height - (m_divY * m_currentDiv[1]) : m_divY; // if last row in grid, use remaining pixels
    m_currentCellNum = c;
    m_log->debug2("getCell(%d) - %d:%d:%d:%d", c, m_currentCell.x, m_currentCell.y, m_currentCell.width, m_currentCell.height);
}

void Menu::drawCell(uint8_t _cellNum) {
    getCell(_cellNum);
    drawBorderAndFill();
    drawLabel();
}

void Menu::drawLabel(uint8_t _cellNum) {
    getCell(_cellNum);
    drawLabel();
}

void Menu::drawLabel() {
    const char *label;
    if (m_labelGetter != NULL) {
        label = m_labelGetter(m_currentCellNum);
        if (label != NULL && strlen(label) > 0) {
            if (m_onCellLabelPrint != NULL) {
                m_onCellLabelPrint(m_tft);
            }
            m_tft->setTextDatum(MC_DATUM);
            m_tft->setTextColor(TFT_WHITE);
            m_tft->drawString(label, m_currentCell.x + (m_currentCell.width / 2), m_currentCell.y + (m_currentCell.height / 2));
        }
    }
}

void Menu::drawBorderAndFill(uint8_t _cellNum) {
    getCell(_cellNum);
    drawBorderAndFill();
}

void Menu::drawBorderAndFill() {
    if (m_currentCellNum == m_selectedChoice) {
        TFTUtils::drawBorderRect(m_tft, m_currentCell, m_fillColorGetter(m_currentCellNum), m_selectedBorderProps);
    } else {
        TFTUtils::drawBorderRect(m_tft, m_currentCell, m_fillColorGetter(m_currentCellNum), m_choiceBorderProps);
    }
}

void Menu::showText(const char *str) {
    m_log->log(str);
}
