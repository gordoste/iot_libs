#ifndef _STRINGUTILS_H
#define _STRINGUTILS_H

#include "Arduino.h"

#include <stdio.h>
#include <string.h>

namespace StringUtils {
    char* strtoke(char *str, const char *delim);
    uint8_t utf8ascii(uint8_t ascii);
    char serialRead();
    // Return number (1-9) of selected choice, or 0 for lastChoice. -1 on error (or user cancelled).
    int8_t multiChoice(const char *choices[], uint8_t numChoices, Stream *out,
        int8_t selectedChoice = -1, const char *lastChoice = NULL, char (*inputRead)() = &serialRead);
    // Return selected choice. -1 on error (or user cancelled).
    char multiChoice(const char *choiceStrings[], const char *choices, Stream *out,
        char selectedChoice = '\0', char (*inputRead)() = &serialRead);        
}

#endif // #ifndef _STRINGUTILS_H