#include "Arduino.h"
#include "LedControl.h"
#include "TextASCII.h"

// Pointers are a peculiar case...typically 16-bit on AVR boards,
// 32 bits elsewhere.  Try to accommodate both...

#ifndef pgm_read_pointer
  #if !defined(__INT_MAX__) || (__INT_MAX__ > 0xFFFF)
    #define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))
  #else
    #define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))
  #endif
#endif

TextASCII::TextASCII(LedControl *lc) {
	_lc = lc;
    _remainingBytes = 0;
}

int TextASCII::copyChar(byte* dst, char c) {
	if (!inRange(c)) { return -1; }
	byte *letter = (byte *)pgm_read_pointer(&(ASCII[c-32]));
	memcpy_P(_colCount, letter, 1);
	memcpy_P(dst, letter+1, *_colCount);
	return *_colCount;
}

void TextASCII::refreshDisplay() {
  for (byte i=0; i<_lc->getDeviceCount(); i++) {
    for (byte j=0; j<8; j++) {
      _lc->setRow(i, j, _dispBuf[(i*8 + j + _offset) % _dispBufLen]);
    }
  }
}

void TextASCII::scrollInit(char *txtBuf, int txtLen) {
  _charLen = 0; // length of this character
  _charIdx = 0;
  _dispBufLen = 8*_lc->getDeviceCount();
  _remainingBytes = _dispBufLen; // Used during scroll-out
  _txtBuf = txtBuf;
  _txtLen = txtLen;
  _txtIdx = 0;
  _offset = 0; // use dispBuf starting here, wrap around from end to start
  memset(_dispBuf, 0, 64); // empty the buffer
  refreshDisplay();
}

void TextASCII::scroll() {
  if (_remainingBytes == 0) { return; } // If we've finished scrolling, just do nothing
  if (_txtIdx < _txtLen) {
	if (_charIdx == _charLen) {
	  _charLen = copyChar(_charBuf, _txtBuf[_txtIdx]); // ... pull another character in
      _charBuf[_charLen++] = 0; // .. and an empty byte
	  _charIdx = 0;
	}
    _dispBuf[_offset++] = _charBuf[_charIdx]; // Put it in the left-most byte, which will become the right-most byte
    if (_offset == _dispBufLen) { _offset = 0; } // Wrap back to start if we reach end
    refreshDisplay();
    _charIdx++;
	if (_charIdx == _charLen) {	_txtIdx++; } // This character is in the display buffer, move to the next one
  } else {
	// Scroll-out - last character has entered buffer. Need to scroll everything across replacing with blanks
    _dispBuf[_offset % _dispBufLen]=0; // Just zero out the left-most byte, which will become the right-most byte
    _offset++;
    refreshDisplay();
	_remainingBytes--;
  }
}

void TextASCII::clear() {
  for (byte i = 0; i<_lc->getDeviceCount(); i++) {
	_lc->clearDisplay(i);
  }	
}

bool TextASCII::isScrolling() {
  return _remainingBytes > 0;
}

bool TextASCII::inRange(char c) {
  return (c >= 32 && c <= 126);	
}