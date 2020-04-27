#include "Menu.h"

void StreamMenu::begin(BasicLog *log, ExtendedSerial *stdIn, Print *stdOut) {
  m_log = log;
  m_stdin = stdIn;
  setOutputStream(stdOut);
}

void StreamMenu::setOutputStream(Print *stdOut) {
  m_stdout = stdOut;
}

// Return number (0-9) of selected choice. -1 on error (or user cancelled).
int8_t StreamMenu::multiChoice(const char *choiceStrings[], uint8_t numChoices, int8_t selectedChoice /* = -1 */) {
  if (numChoices > 9) return -1; // Too many
  while (1) {
    for (uint8_t i = 0; i < numChoices; i++) {
      m_stdout->printf("%d) %s", i+1, choiceStrings[i]);
      if (i == selectedChoice) m_stdout->print("    <<< SELECTED");
      m_stdout->println();
    }
    m_stdout->println(F("X) Cancel."));
    m_stdout->printf("> ");
    char c = m_stdin->timedRead();
    m_stdout->println(c);
    if (c == 'x' || c == 'X') return -1;
    if (c >= '0' && c <='9') {  // A number 
      c -= '0'; // convert ASCII character to int (i.e. '0' => 0, '1' => 1 ...) 
      if (c <= numChoices) return c;
    }
    m_stdout->println(F("Invalid selection."));
  }
  return -1;
}

// Return selected choice. -1 on error (or user cancelled).
char StreamMenu::multiChoice(const char *choiceStrings[], const char *choices, char selectedChoice /* = '\0' */) {
  uint8_t numChoices = strlen(choices);
  while (1) {
    for (uint8_t i = 0; i < numChoices; i++) {
      m_stdout->printf("%c) %s", choices[i], choiceStrings[i]);
      if (choices[i] == selectedChoice) m_stdout->print("    <<< SELECTED");
      m_stdout->println();
    }
    m_stdout->println(F("X) Cancel."));
    m_stdout->printf("> ");
    char c = m_stdin->timedRead();
    m_stdout->println(c);
    if (c == 'x' || c == 'X') return -1;
    if (strchr(choices, c)) return c; // Check if character is a valid selection
    if (c >= 'a' && c <= 'z' && strchr(choices, c - 'a' + 'A')) return c; // if LC, check for UC version
    if (c >= 'A' && c <= 'Z' && strchr(choices, c - 'A' + 'a')) return c; // if UC, check for LC version
    m_stdout->println(F("Invalid selection."));
  }
  return -1;
}

void TFTMenu::begin(BasicLog *log, TFT_eSPI *tft, Window *w) {
  m_log = log;
  m_tft = tft;
  m_win = w;
  m_labelGetter = DEFAULT_LABEL_GETTER;
  m_fillColorGetter = MENU_BLACK_GETTER;
}

TFTMenu *TFTMenu::setBorderProps(LineProperties &_props) {
  m_borderProps.color = _props.color;
  m_borderProps.width = _props.width;
  return this;
}

TFTMenu *TFTMenu::setSelectedBorderProps(LineProperties &_props) {
  m_selectedBorderProps.color = _props.color;
  m_selectedBorderProps.width = _props.width;
  return this;
}

TFTMenu *TFTMenu::setNumChoices(uint8_t _n, uint8_t _x, uint8_t _y) {
  m_numChoices = _n;
  m_xDivs = _x; m_yDivs = _y;
  m_divX = m_win->width/m_xDivs; // size of each cell
  m_divY = m_win->height/m_yDivs;
  m_shown = false;
  setSelectedChoice(-1);
  return this;
}

void TFTMenu::show() {
    m_log->debug2("selectGrid() %d:%d:%d:%d:%d:%d", m_xDivs, m_yDivs, m_numChoices, m_selectedChoice);
    uint8_t cellNum = 0;
    m_log->debug3("sG_begin-%d:%d:%d:%d",m_win->x,m_win->y,m_win->width,m_win->height);
    while (m_currentDiv[0] < m_xDivs && m_currentDiv[1] < m_yDivs && cellNum < m_numChoices) {
      drawCell(cellNum);
      if (++m_currentDiv[0] == m_xDivs) { m_currentDiv[1]++; m_currentDiv[0] = 0; } // Increment cell, move to next row if needed
      cellNum = m_currentDiv[0] + m_currentDiv[1]*m_xDivs;
    }
    m_touchHandler = [this](uint16_t x, uint16_t y) {
       m_currentDiv[0] = 0; m_currentDiv[1] = 0;
       while (x < m_currentDiv[0]*m_divX || x >= ++m_currentDiv[0]*m_divX) {} // Find the col AFTER the one touched
       while (y < m_currentDiv[1]*m_divY || y >= ++m_currentDiv[1]*m_divY) {} // Find the row AFTER the one touched
       m_currentDiv[0]--; m_currentDiv[1]--; // Find the cell touched
       m_selectedChoice = m_currentDiv[0] + m_currentDiv[1]*m_xDivs;
       if (m_selectedChoice >= 0 && m_selectedChoice < m_numChoices) {
         setSelectedChoice(m_selectedChoice);
       }
       else {
         setSelectedChoice(-1);
       }
    };
    m_shown = true;
    m_log->debug2(F("selectGrid() leave"));
    return;
}

int8_t TFTMenu::getSelectedChoice() { return m_selectedChoice; }
TFTMenu *TFTMenu::setSelectedChoice(int8_t _cellNum) {
  if (_cellNum == m_selectedChoice) return this;
  int8_t oldSel = m_selectedChoice;
  m_selectedChoice = _cellNum;
  if (m_shown) {
    drawCell(oldSel); // Redraw previously selected cell
    drawCell(m_selectedChoice); // Draw newly selected cell
  }
  return this;
};

void TFTMenu::getCell(uint8_t c) {
  m_currentDiv[0] = c % m_xDivs;
  m_currentDiv[1] = c / m_xDivs;
  m_currentCell.x = m_win->x + m_currentDiv[0] * m_divX;
  m_currentCell.y = m_win->y + m_currentDiv[1] * m_divY;
  m_currentCell.width = m_currentDiv[0] == m_xDivs-1 ? m_win->width - (m_divX * m_currentDiv[0]) : m_divX;   // if last cell in row, use remaining pixels
  m_currentCell.height = m_currentDiv[1] == m_yDivs-1 ? m_win->height - (m_divY * m_currentDiv[1]) : m_divY; // if last row in grid, use remaining pixels
  m_currentCellNum = c;
  m_log->debug2("getCell(%d) - %d:%d:%d:%d",c,m_currentCell.x,m_currentCell.y,m_currentCell.width,m_currentCell.height);
}

void TFTMenu::drawCell(uint8_t _cellNum) {
  getCell(_cellNum);
  drawBorderAndFill();
  drawLabel();
}

void TFTMenu::drawLabel(uint8_t _cellNum) {
  getCell(_cellNum);
  drawLabel();
}

void TFTMenu::drawLabel() {
  const char *label;
  if (m_labelGetter != NULL) {
    label = m_labelGetter(m_currentCellNum);
    if (label != NULL) {
      if (m_onCellLabelPrint != NULL) { m_onCellLabelPrint(m_tft); }
      m_tft->setTextDatum(MC_DATUM);
      m_tft->setTextColor(TFT_WHITE);
      m_tft->drawString(label, m_currentCell.x + (m_currentCell.width/2), m_currentCell.y + (m_currentCell.height/2));
    }
  }
}

void TFTMenu::drawBorderAndFill(uint8_t _cellNum) {
  getCell(_cellNum);
  drawBorderAndFill();
}

void TFTMenu::drawBorderAndFill() {
  if (m_currentCellNum == m_selectedChoice) {
    TFTUtils::drawBorderRect(m_tft, m_currentCell, m_fillColorGetter(m_currentCellNum), m_selectedBorderProps);
  }
  else {
    TFTUtils::drawBorderRect(m_tft, m_currentCell, m_fillColorGetter(m_currentCellNum), m_borderProps);
  }
}
