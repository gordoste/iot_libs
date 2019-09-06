#ifndef _MENU_H
#define _MENU_H

#include <Arduino.h>
#include "StringUtils.h"

class Menu {
  public:
    // Return number (1-9) of selected choice, or 0 for lastChoice. -1 on error (or user cancelled).
    virtual int8_t multiChoice(const char *choices[], uint8_t numChoices, int8_t selectedChoice, const char *lastChoice);
    // Return selected choice. -1 on error (or user cancelled).
    virtual char multiChoice(const char *choiceStrings[], const char *choices, char selectedChoice);
};

class StreamMenu : Menu {
  public:
    void begin(Stream *stdIn, Print *stdOut);
    // Return number (1-9) of selected choice, or 0 for lastChoice. -1 on error (or user cancelled).
    int8_t multiChoice(const char *choices[], uint8_t numChoices, int8_t selectedChoice = -1, const char *lastChoice = NULL);
    // Return selected choice. -1 on error (or user cancelled).
    char multiChoice(const char *choiceStrings[], const char *choices, char selectedChoice = '\0');
  private:
    Stream *m_stdin;
    Print *m_stdout;
};

#ifdef TFT_ENABLED

#include "TFT_eSPI.h"

class TFTMenu : Menu {
  public:
    void begin(TFT_eSPI *tft);
    // Return number (1-9) of selected choice, or 0 for lastChoice. -1 on error (or user cancelled).
    int8_t multiChoice(const char *choices[], uint8_t numChoices, int8_t selectedChoice = -1, const char *lastChoice = NULL);
    // Return selected choice. -1 on error (or user cancelled).
    char multiChoice(const char *choiceStrings[], const char *choices, char selectedChoice = '\0');
  private:
    TFT_eSPI *m_tft;
};

#endif //#ifdef TFT_ENABLED

#endif //#ifndef _MENU_H