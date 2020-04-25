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
}

// Return number (0-9) of selected choice. -1 on error (or user cancelled).
int8_t TFTMenu::multiChoice(const char *choices[], uint8_t numChoices, int8_t selectedChoice /*= -1*/) {
  m_log->debug3("menuChoice(*,%d,%d)", numChoices, selectedChoice);
  return selectGrid(1, numChoices, numChoices, selectedChoice, choices);
}

// Return selected choice. -1 on error (or user cancelled).
char TFTMenu::multiChoice(const char *choiceStrings[], const char *choices, char selectedChoice /*= '\0'*/) {
  m_log->debug3("menuChoice(*,%s,%c)", choices, selectedChoice == '\0' ? '-' : selectedChoice);
  uint8_t numChoices = strlen(choices);
  int8_t selNum = -1;
  if (selectedChoice != '\0') {
    char *selpos = strchr(choices, selectedChoice);
    selNum = (selpos-choices);
  }
  int8_t r = selectGrid(1, numChoices, numChoices, selNum, choiceStrings);
  if (r == -1) return -1;
  return choices[r];
}

int8_t TFTMenu::selectGrid(int32_t xDivs, int32_t yDivs, uint8_t numChoices, int8_t selectedChoice,
  TLabel_Getter labelGetter,
  const uint32_t colourCombos[], uint8_t numColourCombos, LineProperties borderProps) {
    m_log->debug2("selectGrid() %d:%d:%d:%d:%d:%d", xDivs, yDivs, numChoices, selectedChoice, numColourCombos, borderProps.width);
    divX = m_win->width/xDivs; // size of each cell
    divY = m_win->height/yDivs;
    uint8_t currentDiv[2] = { 0, 0 }; // which cell are we drawing
    uint8_t currentColourCombo = 0;
    Window cell;
    uint8_t cellNum = 0;
    m_log->debug3("sG_begin-%d:%d:%d:%d",m_win->x,m_win->y,m_win->width,m_win->height);
    while (currentDiv[0] < xDivs && currentDiv[1] < yDivs && cellNum < numChoices) {
      cell.x = m_win->x + currentDiv[0] * divX;
      cell.y = m_win->y + currentDiv[1] * divY;
      cell.width = currentDiv[0] == xDivs-1 ? m_win->width - (divX * currentDiv[0]) : divX;   // if last cell in row, use remaining pixels
      cell.height = currentDiv[1] == yDivs-1 ? m_win->height - (divY * currentDiv[1]) : divY; // if last row in grid, use remaining pixels
      m_log->debug2("sG_cell%d - %d:%d:%d:%d",cellNum,cell.x,cell.y,cell.width,cell.height);
      if (cellNum == selectedChoice) {
        TFTUtils::drawBorderRect(m_tft, cell, colourCombos[2*currentColourCombo], { TFT_RED, 3 });
      }
      else {
        TFTUtils::drawBorderRect(m_tft, cell, colourCombos[2*currentColourCombo], borderProps);
      }  
      const char *label;
      if (labelGetter != NULL) {
        label = labelGetter(currentDiv[0] + currentDiv[1]*xDivs);
        if (label != NULL) {
          if (m_onCellLabelPrint != NULL) { m_onCellLabelPrint(m_tft); }
          m_tft->setTextDatum(MC_DATUM);
          m_tft->setTextColor(colourCombos[2*currentColourCombo + 1]);
          m_tft->drawString(label, cell.x + (cell.width/2), cell.y + (cell.height/2));
        }
      }
      currentColourCombo++; currentColourCombo %= numColourCombos;
      if (++currentDiv[0] == xDivs) { currentDiv[1]++; currentDiv[0] = 0; } // Increment cell, move to next row if needed
      cellNum = currentDiv[0] + currentDiv[1]*xDivs;
    }
    uint16_t touchX, touchY;
    int8_t cellSelected = -1;
    while (cellSelected < 0 || cellSelected >= numChoices) { // keep getting touches until a cell is touched
      cellSelected = -1;
      while (!m_tft->getTouch(&touchX, &touchY)) {} 
      currentDiv[0] = 0; currentDiv[1] = 0;
      while (touchX < m_win->x + currentDiv[0]*divX || touchX >= m_win->x + ++currentDiv[0]*divX) {} // Find the col AFTER the one touched
      while (touchY < m_win->y + currentDiv[1]*divY || touchY >= m_win->y + ++currentDiv[1]*divY) {} // Find the row AFTER the one touched
      currentDiv[0]--; currentDiv[1]--; // Find the cell touched
      cellSelected = currentDiv[0] + currentDiv[1]*xDivs;
    }
    m_tft->fillScreen(TFT_BLACK);
    m_log->debug2(F("selectGrid() leave"));
    return cellSelected;
}

int8_t TFTMenu::selectGrid(int32_t xDivs, int32_t yDivs, uint8_t numChoices, int8_t selectedChoice,
  const char *cellLabels[],
  const uint32_t colourCombos[], uint8_t numColourCombos, LineProperties borderProps) {
    if (cellLabels != NULL) {
      m_cellLabels = cellLabels;
      return selectGrid(xDivs, yDivs, numChoices, selectedChoice,
        [this](uint8_t i){return m_cellLabels[i];}, 
        colourCombos, numColourCombos, borderProps);
    }
    else {
      return selectGrid(xDivs, yDivs, numChoices, selectedChoice,
        [this](uint8_t i){return (const char *)NULL;}, 
        colourCombos, numColourCombos, borderProps);
    }
}
