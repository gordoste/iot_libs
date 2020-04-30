#ifndef _STREAMMENU_H
#define _STREAMMENU_H

#include "BasicLog.h"
#include "ExtendedSerial.h"
#include "StringUtils.h"
#include <Arduino.h>

class StreamMenu {
public:
    void begin(BasicLog *log, ExtendedSerial *stdIn, Print *stdOut);
    void setOutputStream(Print *stdOut);
    // Return number (0-9) of selected choice. -1 on error (or user cancelled).
    int8_t multiChoice(const char *choices[], uint8_t numChoices, int8_t selectedChoice = -1);
    // Return selected choice. -1 on error (or user cancelled).
    char multiChoice(const char *choiceStrings[], const char *choices, char selectedChoice = '\0');

protected:
    BasicLog *m_log;
    ExtendedSerial *m_stdin;
    Print *m_stdout;
};

#endif //#ifndef _STREAMMENU_H