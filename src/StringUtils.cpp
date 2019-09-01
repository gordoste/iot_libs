#include "StringUtils.h"

static uint8_t c1;  // Last character buffer

// Behaves like strtok() except that it returns empty tokens also
char* StringUtils::strtoke(char *str, const char *delim)
{
  static char *start = NULL; /* stores string str for consecutive calls */
  char *token = NULL; /* found token */
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


// ****** UTF8-Decoder: convert UTF8-string to extended ASCII *******
// Convert a single Character from UTF8 to Extended ASCII
// Return "0" if a byte has to be ignored
uint8_t StringUtils::utf8ascii(uint8_t ascii) {
  if (ascii < 128) {   // Standard ASCII-set 0..0x7F handling
    c1 = 0;
    return ascii;
  }

  // get previous input
  uint8_t last = c1;   // get last char
  c1 = ascii;         // remember actual character

  switch (last) {   // conversion depending on first UTF8-character
    case 0xC2: return ascii; break;
    case 0xC3: return (ascii | 0xC0); break;
    case 0x82: if (ascii==0xAC) return 0x80;       // special case Euro-symbol
  }

  return 0;                                     // otherwise: return zero, if character has to be ignored
}

char StringUtils::serialRead() { return Serial.read(); }

// Return number (1-9) of selected choice, or 0 for lastChoice. -1 on error (or user cancelled).
int8_t StringUtils::multiChoice(const char *choiceStrings[], uint8_t numChoices, Stream *out,
  int8_t selectedChoice /* = -1 */, const char *lastChoice /* = NULL */,
  char (*inputRead)() /* = &serialRead */) {
  if (numChoices > 9) return -1; // Too many
  while (1) {
    for (uint8_t i = 0; i < numChoices; i++) {
      out->printf("%d) %s", i+1, choiceStrings[i]);
      if (i == selectedChoice) out->print("    <<< SELECTED");
      out->println();
    }
    if (lastChoice) out->printf("0) %s\n", lastChoice);
    out->println(F("X) Cancel."));
    out->printf("< ");
    char c = (*inputRead)();
    out->println(c);
    if (c == 'x' || c == 'X') return -1;
    if (c == '0' && lastChoice != NULL) return 0;
    if (c >= '1' && c <='9') {  // A number 
      c -= '0'; // convert ASCII character to int (i.e. '1' => 1, '2' => 2 ...) 
      if (c <= numChoices) return c;
    }
    out->println(F("Invalid selection."));
  }
  return -1;
}

// Return selected choice. -1 on error (or user cancelled).
char StringUtils::multiChoice(const char *choiceStrings[], const char *choices, Stream *out,
  char selectedChoice /* = '\0' */, char (*inputRead)() /* = &serialRead */) {
  uint8_t numChoices = strlen(choices);
  while (1) {
    for (uint8_t i = 0; i < numChoices; i++) {
      out->printf("%c) %s", choices[i], choiceStrings[i]);
      if (choices[i] == selectedChoice) out->print("    <<< SELECTED");
      out->println();
    }
    out->println(F("X) Cancel."));
    out->printf("< ");
    char c = (*inputRead)();
    out->println(c);
    if (c == 'x' || c == 'X') return -1;
    if (strchr(choices, c)) return c; // Check if character is a valid selection
    if (c >= 'a' && c <= 'z' && strchr(choices, c - 'a' + 'A')) return c; // if LC, check for UC version
    if (c >= 'A' && c <= 'Z' && strchr(choices, c - 'A' + 'a')) return c; // if UC, check for LC version
    out->println(F("Invalid selection."));
  }
  return -1;
}
