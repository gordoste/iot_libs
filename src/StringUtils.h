#ifndef _STRINGUTILS_H
#define _STRINGUTILS_H

#include <Arduino.h>
#include <IPAddress.h>

#include <stdio.h>
#include <string.h>

#define IP_PORT_MAXLEN 24 // 3+1+3+1+3+1+3 + 1 + 5 + 1 (plus couple extra)

namespace StringUtils {
char *strtoke(char *str, const char *delim);
void strrepl(char *str, char find, char repl);
uint8_t utf8ascii(uint8_t ascii);
bool parseIPAndPort(const char *str, IPAddress &dstIP, uint16_t &dstPort);
} // namespace StringUtils

#endif // #ifndef _STRINGUTILS_H