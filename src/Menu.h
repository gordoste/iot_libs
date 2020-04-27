#ifndef _MENU_H
#define _MENU_H

#include <Arduino.h>
#include "ExtendedSerial.h"
#include "BasicLog.h"
#include "StringUtils.h"

class Menu {
  public:
    // Return number (0-9) of selected choice. -1 on error (or user cancelled).
    virtual int8_t multiChoice(const char *choices[], uint8_t numChoices, int8_t selectedChoice) = 0;
    // Return selected choice. -1 on error (or user cancelled).
    virtual char multiChoice(const char *choiceStrings[], const char *choices, char selectedChoice) = 0;
  protected:
    BasicLog *m_log;
};

class StreamMenu : public Menu {
  public:
    void begin(BasicLog *log, ExtendedSerial *stdIn, Print *stdOut);
    void setOutputStream(Print *stdOut);
    // Return number (0-9) of selected choice. -1 on error (or user cancelled).
    int8_t multiChoice(const char *choices[], uint8_t numChoices, int8_t selectedChoice = -1);
    // Return selected choice. -1 on error (or user cancelled).
    char multiChoice(const char *choiceStrings[], const char *choices, char selectedChoice = '\0');
  protected:
    ExtendedSerial *m_stdin;
    Print *m_stdout;
};

#ifdef TFT_ENABLED

#define MAX_CHOICES 20

#include "TFT_eSPI.h"
#include "TFTUtils.h"

typedef std::function<const char *(uint8_t cell_nr)> TLabel_Getter;
typedef std::function<uint32_t(uint8_t cell_nr)> TColor_Getter;

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

class TFTMenu : public TouchControl {
  static const char *DEFAULT_LABEL_GETTER(uint8_t _cellNum) { return "-"; }
  static uint32_t MENU_WHITE_GETTER(uint8_t _cellNum) { return TFT_WHITE; }
  static uint32_t MENU_BLACK_GETTER(uint8_t _cellNum) { return TFT_BLACK; }

  public:
    void begin(BasicLog *log, TFT_eSPI *tft, Window *win);
    void onCellLabelPrint(TFTHandler fn) { m_onCellLabelPrint = fn; };

    void show();

    int8_t getSelectedChoice();
    TFTMenu *setSelectedChoice(int8_t c);

    TFTMenu *setBorderProps(LineProperties &_props);
    TFTMenu *setSelectedBorderProps(LineProperties &_props);

    TFTMenu *setNumChoices(uint8_t _n, uint8_t _x, uint8_t _y);
    TFTMenu *setNumChoices(uint8_t _n) { return setNumChoices(_n, 1, _n); };

    TFTMenu *setLabelGetter(TLabel_Getter _lg) { m_labelGetter = _lg; return this; }
    TFTMenu *setFillColorGetter(TColor_Getter _cg) { m_fillColorGetter = _cg; return this; }
  protected:
    BasicLog *m_log;
    TFT_eSPI *m_tft;
    Window *m_win;
    bool m_shown = false;
    TFTHandler m_onCellLabelPrint = NULL;
    const char **m_cellLabels;
    const char *m_allChoices[MAX_CHOICES];
    uint32_t m_divX, m_divY;
    uint8_t m_currentDiv[2] = { 0, 0 }; // which cell are we drawing
    uint8_t m_xDivs, m_yDivs;
    uint8_t m_selectedChoice;
    uint8_t m_numChoices;
    Window m_currentCell;
    uint8_t m_currentCellNum;
    TLabel_Getter m_labelGetter;
    TColor_Getter m_fillColorGetter;
    LineProperties m_borderProps = DefaultBorder;
    LineProperties m_selectedBorderProps = { TFT_RED, 3 };

  private:
    void getCell(uint8_t c);
    void drawCell(uint8_t _cellNum);
    void drawLabel(uint8_t _cellNum);
    void drawBorderAndFill(uint8_t _cellNum);
    void drawCell();
    void drawLabel();
    void drawBorderAndFill();
};

#endif //#ifdef TFT_ENABLED

#endif //#ifndef _MENU_H