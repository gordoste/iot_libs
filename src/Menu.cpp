#include "Menu.h"

void StreamMenu::begin(ExtendedSerial *stdIn, Print *stdOut) {
  m_stdin = stdIn;
  m_stdout = stdOut;
}

// Return number (1-9) of selected choice, or 0 for lastChoice. -1 on error (or user cancelled).
int8_t StreamMenu::multiChoice(const char *choiceStrings[], uint8_t numChoices,
  int8_t selectedChoice /* = -1 */, const char *lastChoice /* = NULL */) {
  if (numChoices > 9) return -1; // Too many
  while (1) {
    for (uint8_t i = 0; i < numChoices; i++) {
      m_stdout->printf("%d) %s", i+1, choiceStrings[i]);
      if (i == selectedChoice) m_stdout->print("    <<< SELECTED");
      m_stdout->println();
    }
    if (lastChoice) m_stdout->printf("0) %s\n", lastChoice);
    m_stdout->println(F("X) Cancel."));
    m_stdout->printf("> ");
    char c = m_stdin->timedRead();
    m_stdout->println(c);
    if (c == 'x' || c == 'X') return -1;
    if (c == '0' && lastChoice != NULL) return 0;
    if (c >= '1' && c <='9') {  // A number 
      c -= '0'; // convert ASCII character to int (i.e. '1' => 1, '2' => 2 ...) 
      if (c <= numChoices) return c;
    }
    m_stdout->println(F("Invalid selection."));
  }
  return -1;
}

// Return selected choice. -1 on error (or user cancelled).
char StreamMenu::multiChoice(const char *choiceStrings[], const char *choices, char selectedChoice /* = '\0' */) {
  uint8_t numChoices = strlen(choices);
  while (1) {
    for (uint8_t i = 0; i < numChoices; i++) {
      m_stdout->printf("%c) %s", choices[i], choiceStrings[i]);
      if (choices[i] == selectedChoice) m_stdout->print("    <<< SELECTED");
      m_stdout->println();
    }
    m_stdout->println(F("X) Cancel."));
    m_stdout->printf("> ");
    char c = m_stdin->timedRead();
    m_stdout->println(c);
    if (c == 'x' || c == 'X') return -1;
    if (strchr(choices, c)) return c; // Check if character is a valid selection
    if (c >= 'a' && c <= 'z' && strchr(choices, c - 'a' + 'A')) return c; // if LC, check for UC version
    if (c >= 'A' && c <= 'Z' && strchr(choices, c - 'A' + 'a')) return c; // if UC, check for LC version
    m_stdout->println(F("Invalid selection."));
  }
  return -1;
}