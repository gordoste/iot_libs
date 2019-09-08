#include "Menu.h"

void StreamMenu::begin(ExtendedSerial *stdIn, Print *stdOut) {
  m_stdin = stdIn;
  m_stdout = stdOut;
}

// Return number (1-9) of selected choice, or 0 for lastChoice. -1 on error (or user cancelled).
int8_t StreamMenu::multiChoice(const char *choiceStrings[], uint8_t numChoices,
  int8_t selectedChoice /* = -1 */, const char *lastChoice /* = NULL */) {
  if (numChoices > 9) return -1; // Too many
  while (1) {
    for (uint8_t i = 0; i < numChoices; i++) {
      m_stdout->printf("%d) %s", i+1, choiceStrings[i]);
      if (i == selectedChoice) m_stdout->print("    <<< SELECTED");
      m_stdout->println();
    }
    if (lastChoice) m_stdout->printf("0) %s\n", lastChoice);
    m_stdout->println(F("X) Cancel."));
    m_stdout->printf("> ");
    char c = m_stdin->timedRead();
    m_stdout->println(c);
    if (c == 'x' || c == 'X') return -1;
    if (c == '0' && lastChoice != NULL) return 0;
    if (c >= '1' && c <='9') {  // A number 
      c -= '0'; // convert ASCII character to int (i.e. '1' => 1, '2' => 2 ...) 
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

void TFTMenu::begin(TFT_eSPI *tft) { m_tft = tft; }

// Return number (1-9) of selected choice, or 0 for lastChoice. -1 on error (or user cancelled).
int8_t TFTMenu::multiChoice(const char *choices[], uint8_t numChoices,
  int8_t selectedChoice /*= -1*/, const char *lastChoice /*= NULL*/) {
}

// Return selected choice. -1 on error (or user cancelled).
char TFTMenu::multiChoice(const char *choiceStrings[], const char *choices, char selectedChoice /*= '\0'*/) {
  uint8_t numChoices = strlen(choices);
  uint8_t size = sqrt(numChoices)+1;
  Window win = { 0, 0, m_tft->width(), m_tft->height()-100 };
  int8_t r = selectGrid(win, size, size, numChoices, menuColourCombos, NUM_COMBOS, TFT_WHITE, 1, choiceStrings);
  if (r == -1) return -1;
  return choices[r];
}


void TFTMenu::drawBorderRect(Window win, uint32_t borderColor, uint32_t fillColor, uint8_t borderWidth /*= 1*/) {
  for (int i = 0; i < borderWidth; i++) {
    m_tft->drawRect(win.x+i, win.y+i, win.width-(2*i), win.height-(2*i), borderColor);
  }
  m_tft->fillRect(win.x+borderWidth, win.y+borderWidth, win.width-2*borderWidth, win.height-2*borderWidth, fillColor);
}

int8_t TFTMenu::selectGrid(Window win, int32_t xDivs, int32_t yDivs, uint8_t numChoices, TCellLabel_Getter labelGetter,
  const uint32_t colourCombos[], uint8_t numColourCombos, uint32_t borderColor, uint8_t borderWidth) {
    uint32_t divX = win.width/xDivs; // size of each cell
    uint32_t divY = win.height/yDivs;
    uint8_t currentDiv[2] = { 0, 0 }; // which cell are we drawing
    uint8_t currentColourCombo = 0;
    Window cell;
    while (currentDiv[0] < xDivs && currentDiv[1] < yDivs && (currentDiv[0] + currentDiv[1]*xDivs) < numChoices) {
      cell.x = win.x + currentDiv[0] * divX;
      cell.y = win.y + currentDiv[1] * divY;
      cell.width = currentDiv[0] == xDivs-1 ? win.width - (divX * currentDiv[0]) : divX;   // if last cell in row, use remaining pixels
      cell.height = currentDiv[1] == yDivs-1 ? win.height - (divY * currentDiv[1]) : divY; // if last row in grid, use remaining pixels
      drawBorderRect(cell, TFT_WHITE, colourCombos[2*currentColourCombo]);
      const char *label;
      if (labelGetter != NULL) {
        label = labelGetter(currentDiv[0] + currentDiv[1]*xDivs);
        if (label != NULL) {
          m_tft->setCursor(win.x + currentDiv[0]*divX + 2, win.y + currentDiv[1]*divY + 2);
          m_tft->setTextColor(colourCombos[2*currentColourCombo + 1]);
          m_tft->printf(label);
        }
      }
      currentColourCombo++; currentColourCombo %= numColourCombos;
      if (++currentDiv[0] == xDivs) { currentDiv[1]++; currentDiv[0] = 0; } // Increment cell, move to next row if needed
    }
    uint16_t touchX, touchY;
    int8_t cellSelected = -1;
    while (cellSelected < 0 || cellSelected >= numChoices) {
      cellSelected = -1;
      while (!m_tft->getTouch(&touchX, &touchY)) {} 
      currentDiv[0] = 0; currentDiv[1] = 0;
      while (touchX < win.x + currentDiv[0]*divX || touchX >= win.x + ++currentDiv[0]*divX) {} // Find the col AFTER the one touched
      while (touchY < win.y + currentDiv[1]*divY || touchY >= win.y + ++currentDiv[1]*divY) {} // Find the row AFTER the one touched
      currentDiv[0]--; currentDiv[1]--; // Find the cell touched
      if (currentDiv[0] == xDivs || currentDiv[1] == yDivs) return -1;
      cellSelected = currentDiv[0] + currentDiv[1]*xDivs;
    }
    return cellSelected;
}

int8_t TFTMenu::selectGrid(Window win, int32_t xDivs, int32_t yDivs, uint8_t numChoices,
  const uint32_t colourCombos[], uint8_t numColourCombos, uint32_t borderColor, uint8_t borderWidth,
  const char *cellLabels[]) {
    if (cellLabels != NULL) {
      m_cellLabels = cellLabels;
      return selectGrid(win,xDivs,yDivs,numChoices,[this](uint8_t i){return m_cellLabels[i];},
        colourCombos,numColourCombos,borderColor,borderWidth);//this->getCellLabel);
    }
    else {
      return selectGrid(win,xDivs,yDivs,numChoices,[this](uint8_t i){return (const char *)NULL;},
        colourCombos,numColourCombos,borderColor,borderWidth);
    }
}
