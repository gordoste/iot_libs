#include "StringUtils.h"

// Behaves like strtok() except that it returns empty tokens also
char *StringUtils::strtoke(char *str, const char *delim) {
    static char *start = NULL; /* stores string str for consecutive calls */
    char *token = NULL;        /* found token */
    /* assign new start in case */
    if (str) start = str;
    /* check whether text to parse left */
    if (!start) return NULL;
    /* remember current start as found token */
    token = start;
    /* find next occurrence of delim */
    start = strpbrk(start, delim);
    /* replace delim with terminator and move start to follower */
    if (start) *start++ = '\0';
    /* done */
    return token;
}

void StringUtils::strrepl(char *str, char find, char repl) {
    for (uint8_t i = 0; i < strlen(str); i++) {
        if (str[i] == find) str[i] = repl;
    }
}

// ****** UTF8-Decoder: convert UTF8-string to extended ASCII *******
// Convert a single Character from UTF8 to Extended ASCII
// Return "0" if a byte has to be ignored
uint8_t StringUtils::utf8ascii(uint8_t ascii) {
    static uint8_t _c1; // Last character buffer
    if (ascii < 128) {  // Standard ASCII-set 0..0x7F handling
        _c1 = 0;
        return ascii;
    }

    // get previous input
    uint8_t last = _c1; // get last char
    _c1 = ascii;        // remember actual character

    switch (last) { // conversion depending on first UTF8-character
    case 0xC2:
        return ascii;
        break;
    case 0xC3:
        return (ascii | 0xC0);
        break;
    case 0x82:
        if (ascii == 0xAC) return 0x80; // special case Euro-symbol
    }

    return 0; // otherwise: return zero, if character has to be ignored
}

// Parse a string that should contain IP:port into given variables
bool StringUtils::parseIPAndPort(const char *str, IPAddress &dstIP, uint16_t &dstPort) {
    static char _tmpBuf[IP_PORT_MAXLEN];
    IPAddress newAddr;
    int newport = -1;
    char *ptr;
    uint8_t len;
    ptr = strchr(str, '|');
    len = (ptr == NULL ? strlen(str) : ptr - str);
    strncpy(_tmpBuf, str, len);
    _tmpBuf[len] = '\0';
    ptr = StringUtils::strtoke(_tmpBuf, ":");
    if (ptr == NULL) return false;
    if (!newAddr.fromString(ptr)) return false;
    ptr = StringUtils::strtoke(NULL, "|");
    newport = atoi(ptr);
    if (newport == -1) return false;
    dstIP = newAddr;
    dstPort = newport;
    return true;
}
