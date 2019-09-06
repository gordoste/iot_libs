#ifndef _STRINGUTILS_H
#define _STRINGUTILS_H

#include "Arduino.h"

#include <stdio.h>
#include <string.h>

namespace StringUtils {
    char* strtoke(char *str, const char *delim);
    uint8_t utf8ascii(uint8_t ascii);
    char serialRead();
}

#endif // #ifndef _STRINGUTILS_H