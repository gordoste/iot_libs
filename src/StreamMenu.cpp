#include "StreamMenu.h"

void StreamMenu::begin(BasicLog *log, ExtendedSerial *stdIn, Print *stdOut) {
    m_log = log;
    m_stdin = stdIn;
    setOutputStream(stdOut);
}

void StreamMenu::setOutputStream(Print *stdOut) {
    m_stdout = stdOut;
}

// Return number (0-9) of selected choice. -1 on error (or user cancelled).
int8_t StreamMenu::multiChoice(const char *choiceStrings[], uint8_t numChoices, int8_t selectedChoice /* = -1 */) {
    if (numChoices > 9) return -1; // Too many
    while (1) {
        for (uint8_t i = 0; i < numChoices; i++) {
            m_stdout->printf("%d) %s", i + 1, choiceStrings[i]);
            if (i == selectedChoice) m_stdout->print("    <<< SELECTED");
            m_stdout->println();
        }
        m_stdout->println(F("X) Cancel."));
        m_stdout->printf("> ");
        char c = m_stdin->timedRead();
        m_stdout->println(c);
        if (c == 'x' || c == 'X') return -1;
        if (c >= '0' && c <= '9') { // A number
            c -= '0';               // convert ASCII character to int (i.e. '0' => 0, '1' => 1 ...)
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
        if (strchr(choices, c)) return c;                                     // Check if character is a valid selection
        if (c >= 'a' && c <= 'z' && strchr(choices, c - 'a' + 'A')) return c; // if LC, check for UC version
        if (c >= 'A' && c <= 'Z' && strchr(choices, c - 'A' + 'a')) return c; // if UC, check for LC version
        m_stdout->println(F("Invalid selection."));
    }
    return -1;
}
