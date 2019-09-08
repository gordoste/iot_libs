#ifndef _MENU_H
#define _MENU_H

#include <Arduino.h>
#include "ExtendedSerial.h"
#include "StringUtils.h"

class Menu {
  public:
    // Return number (1-9) of selected choice, or 0 for lastChoice. -1 on error (or user cancelled).
    virtual int8_t multiChoice(const char *choices[], uint8_t numChoices, int8_t selectedChoice, const char *lastChoice) = 0;
    // Return selected choice. -1 on error (or user cancelled).
    virtual char multiChoice(const char *choiceStrings[], const char *choices, char selectedChoice) = 0;
};

class StreamMenu : public Menu {
  public:
    void begin(ExtendedSerial *stdIn, Print *stdOut);
    // Return number (1-9) of selected choice, or 0 for lastChoice. -1 on error (or user cancelled).
    int8_t multiChoice(const char *choices[], uint8_t numChoices, int8_t selectedChoice = -1, const char *lastChoice = NULL);
    // Return selected choice. -1 on error (or user cancelled).
    char multiChoice(const char *choiceStrings[], const char *choices, char selectedChoice = '\0');
  protected:
    ExtendedSerial *m_stdin;
    Print *m_stdout;
};

#ifdef TFT_ENABLED

#include "TFT_eSPI.h"

typedef std::function<const char *(uint8_t cell_nr)> TCellLabel_Getter;

struct Window {
  uint32_t x;
  uint32_t y;
  int16_t width;
  int16_t height;
};

#define NUM_COMBOS 6
const uint32_t menuColourCombos[2*NUM_COMBOS] = {
  // Fill colout    Text colour
  TFT_YELLOW,       TFT_BLACK,
  TFT_ORANGE,       TFT_BLACK,
  TFT_BLUE,         TFT_WHITE,
  TFT_CYAN,         TFT_BLACK,
  TFT_MAGENTA,      TFT_BLACK,
  TFT_DARKGREEN,    TFT_WHITE,
};

class TFTMenu : public Menu {
  public:
    void begin(TFT_eSPI *tft);
    // Return number (1-9) of selected choice, or 0 for lastChoice. -1 on error (or user cancelled).
    int8_t multiChoice(const char *choices[], uint8_t numChoices, int8_t selectedChoice = -1, const char *lastChoice = NULL);
    // Return selected choice. -1 on error (or user cancelled).
    char multiChoice(const char *choiceStrings[], const char *choices, char selectedChoice = '\0');
    void drawBorderRect(Window win, uint32_t borderColor, uint32_t fillColor, uint8_t borderWidth = 1);
    const char *getCellLabel(uint8_t cell_nr) { return m_cellLabels[cell_nr]; }
    int8_t selectGrid(Window win, int32_t xDivs, int32_t yDivs, uint8_t numChoices, TCellLabel_Getter labelGetter,
      const uint32_t colourCombos[], uint8_t numColourCombos, uint32_t borderColor = TFT_WHITE, uint8_t borderWidth = 1);
    int8_t selectGrid(Window win, int32_t xDivs, int32_t yDivs, uint8_t numChoices,
      const uint32_t colourCombos[], uint8_t numColourCombos, uint32_t borderColor = TFT_WHITE, uint8_t borderWidth = 1,
      const char *cellLabels[] = NULL);
  protected:
    TFT_eSPI *m_tft;
    const char **m_cellLabels;
};

#endif //#ifdef TFT_ENABLED

#endif //#ifndef _MENU_H