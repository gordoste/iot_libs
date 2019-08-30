#ifndef _STRINGUTILS_H
#define _STRINGUTILS_H

#include "Arduino.h"

#include <stdio.h>
#include <string.h>

namespace StringUtils {
    char* strtoke(char *str, const char *delim);
    static uint8_t c1;  // Last character buffer
    uint8_t utf8ascii(uint8_t ascii);
}

#endif // #ifndef _STRINGUTILS_H