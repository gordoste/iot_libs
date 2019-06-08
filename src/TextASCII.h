#include "Arduino.h"
#include "LedControl.h"

#ifndef TEXTASCII_H
#define TEXTASCII_H

#ifdef TEXTASCII_COLS

const PROGMEM byte char00[] = { 3, B00000000, B00000000, B00000000                       }; // space
const PROGMEM byte char01[] = { 1, B11111010                                             }; // !
const PROGMEM byte char02[] = { 3, B11000000, B00000000, B11000000                       }; // "
const PROGMEM byte char03[] = { 5, B00100100, B01111110, B00100100, B01111110, B00100100 }; // #
const PROGMEM byte char04[] = { 4, B00100100, B01010110, B11010100, B01001000            }; // $
const PROGMEM byte char05[] = { 5, B11000110, B11001000, B00010000, B00100110, B11000110 }; // %
const PROGMEM byte char06[] = { 5, B01101100, B10010010, B01101010, B00000100, B00001010 }; // &
const PROGMEM byte char07[] = { 1, B11000000                                             }; // '
const PROGMEM byte char08[] = { 3, B00111000, B01000100, B10000010                       }; // (
const PROGMEM byte char09[] = { 3, B10000010, B01000100, B00111000                       }; // )
const PROGMEM byte char10[] = { 5, B00010100, B00011000, B01110000, B00011000, B00010100 }; // *
const PROGMEM byte char11[] = { 5, B00010000, B00010000, B01111100, B00010000, B00010000 }; // +
const PROGMEM byte char12[] = { 2, B00001101, B00001110                                  }; // ,
const PROGMEM byte char13[] = { 4, B00010000, B00010000, B00010000, B00010000            }; // -
const PROGMEM byte char14[] = { 2, B00000110, B00000110                                  }; // .
const PROGMEM byte char15[] = { 4, B00000110, B00011000, B01100000, B10000000            }; // /
const PROGMEM byte char16[] = { 4, B01111100, B10000010, B10000010, B01111100            }; // 0
const PROGMEM byte char17[] = { 3, B01000010, B11111110, B00000010                       }; // 1
const PROGMEM byte char18[] = { 4, B01000110, B10001010, B10010010, B01100010            }; // 2
const PROGMEM byte char19[] = { 4, B01000100, B10000010, B10010010, B01101100            }; // 3
const PROGMEM byte char20[] = { 4, B00011000, B00101000, B01001000, B11111110            }; // 4
const PROGMEM byte char21[] = { 4, B11100100, B10100010, B10100010, B10011100            }; // 5
const PROGMEM byte char22[] = { 4, B01111100, B10010010, B10010010, B00001100            }; // 6
const PROGMEM byte char23[] = { 4, B10000110, B10001000, B10010000, B11100000            }; // 7
const PROGMEM byte char24[] = { 4, B01101100, B10010010, B10010010, B01101100            }; // 8
const PROGMEM byte char25[] = { 4, B01100000, B10010010, B10010010, B01111100            }; // 9
const PROGMEM byte char26[] = { 1, B00001010                                             }; // :
const PROGMEM byte char27[] = { 2, B00000001, B00001010                                  }; // ;
const PROGMEM byte char28[] = { 3, B00001000, B00010100, B00100010                       }; // <
const PROGMEM byte char29[] = { 3, B00101000, B00101000, B00101000                       }; // =
const PROGMEM byte char30[] = { 3, B00100010, B00010100, B00001000                       }; // >
const PROGMEM byte char31[] = { 4, B01000000, B10011010, B10010000, B01100000            }; // ?
const PROGMEM byte char32[] = { 5, B01111100, B10010010, B10101010, B10111010, B01110000 }; // @
const PROGMEM byte char33[] = { 4, B01111110, B10001000, B10001000, B01111110            }; // A
const PROGMEM byte char34[] = { 4, B11111110, B10010010, B10010010, B01101100            }; // B
const PROGMEM byte char35[] = { 4, B01111100, B10000010, B10000010, B01000100            }; // C
const PROGMEM byte char36[] = { 4, B11111110, B10000010, B10000010, B01111100            }; // D
const PROGMEM byte char37[] = { 4, B11111110, B10010010, B10010010, B10000010            }; // E
const PROGMEM byte char38[] = { 4, B11111110, B10010000, B10010000, B10000000            }; // F
const PROGMEM byte char39[] = { 4, B01111100, B10000010, B10010010, B01011110            }; // G
const PROGMEM byte char40[] = { 4, B11111110, B00010000, B00010000, B11111110            }; // H
const PROGMEM byte char41[] = { 3, B10000010, B11111110, B10000010                       }; // I
const PROGMEM byte char42[] = { 4, B00001100, B00000010, B10000010, B11111100            }; // J
const PROGMEM byte char43[] = { 4, B11111110, B00010000, B00101000, B11000110            }; // K
const PROGMEM byte char44[] = { 4, B11111110, B00000010, B00000010, B00000010            }; // L
const PROGMEM byte char45[] = { 5, B11111110, B01000000, B00110000, B01000000, B11111110 }; // M
const PROGMEM byte char46[] = { 5, B11111110, B00100000, B00010000, B00001000, B11111110 }; // N
const PROGMEM byte char47[] = { 4, B01111100, B10000010, B10000010, B01111100            }; // O
const PROGMEM byte char48[] = { 4, B11111110, B10010000, B10010000, B01100000            }; // P
const PROGMEM byte char49[] = { 4, B01111100, B10000010, B10000010, B01111101            }; // Q
const PROGMEM byte char50[] = { 4, B11111110, B10010000, B10010000, B01101110            }; // R
const PROGMEM byte char51[] = { 4, B01100010, B10010010, B10010010, B01001100            }; // S
const PROGMEM byte char52[] = { 5, B10000000, B10000000, B11111110, B10000000, B10000000 }; // T
const PROGMEM byte char53[] = { 4, B11111100, B00000010, B00000010, B11111100            }; // U
const PROGMEM byte char54[] = { 5, B11110000, B00001100, B00000010, B00001100, B11110000 }; // V
const PROGMEM byte char55[] = { 5, B11111100, B00000010, B00011100, B00000010, B11111100 }; // W
const PROGMEM byte char56[] = { 5, B11000110, B00101000, B00010000, B00101000, B11000110 }; // X
const PROGMEM byte char57[] = { 5, B11100000, B00010000, B00001110, B00010000, B11100000 }; // Y
const PROGMEM byte char58[] = { 4, B10000110, B10001010, B10010010, B11100010            }; // Z
const PROGMEM byte char59[] = { 2, B11111110, B10000010                                  }; // [
const PROGMEM byte char60[] = { 4, B10000000, B01100000, B00011000, B00000110            }; // backslash
const PROGMEM byte char61[] = { 2, B10000010, B11111110                                  }; // ]
const PROGMEM byte char62[] = { 3, B01000000, B10000000, B01000000                       }; // ^
const PROGMEM byte char63[] = { 4, B00000010, B00000010, B00000010, B00000010            }; // _
const PROGMEM byte char64[] = { 2, B10000000, B01000000                                  }; // `
const PROGMEM byte char65[] = { 4, B00000100, B00101010, B00101010, B00011110            }; // a
const PROGMEM byte char66[] = { 4, B11111110, B00100010, B00100010, B00011100            }; // b
const PROGMEM byte char67[] = { 4, B00011100, B00100010, B00100010, B00010100            }; // c
const PROGMEM byte char68[] = { 4, B00011100, B00100010, B00100010, B11111110            }; // d
const PROGMEM byte char69[] = { 4, B00011100, B00101010, B00101010, B00011000            }; // e
const PROGMEM byte char70[] = { 3, B00100000, B01111110, B10100000                       }; // f
const PROGMEM byte char71[] = { 4, B00011001, B00100101, B00100101, B00011110            }; // g
const PROGMEM byte char72[] = { 4, B11111110, B00100000, B00100000, B00011110            }; // h
const PROGMEM byte char73[] = { 3, B00100010, B10111110, B00000010                       }; // i
const PROGMEM byte char74[] = { 4, B00000010, B00000001, B00100001, B10111110            }; // j
const PROGMEM byte char75[] = { 4, B11111110, B00001000, B00010100, B00100010            }; // k
const PROGMEM byte char76[] = { 3, B10000010, B11111110, B00000010                       }; // l
const PROGMEM byte char77[] = { 5, B00111110, B00100000, B00111110, B00100000, B00011110 }; // m
const PROGMEM byte char78[] = { 4, B00111110, B00100000, B00100000, B00011110            }; // n
const PROGMEM byte char79[] = { 4, B00011100, B00100010, B00100010, B00011100            }; // o
const PROGMEM byte char80[] = { 4, B00111111, B00100100, B00100100, B00011000            }; // p
const PROGMEM byte char81[] = { 4, B00011000, B00100100, B00100100, B00111111            }; // q
const PROGMEM byte char82[] = { 4, B00111110, B00010000, B00100000, B00100000            }; // r
const PROGMEM byte char83[] = { 4, B00010010, B00101010, B00101010, B00100100            }; // s
const PROGMEM byte char84[] = { 3, B00100000, B11111100, B00100010                       }; // t
const PROGMEM byte char85[] = { 4, B00111100, B00000010, B00000010, B00111110            }; // u
const PROGMEM byte char86[] = { 5, B00111000, B00000100, B00000010, B00000100, B00111000 }; // v
const PROGMEM byte char87[] = { 5, B00111100, B00000010, B00111100, B00000010, B00111100 }; // w
const PROGMEM byte char88[] = { 5, B00100010, B00010100, B00001000, B00010100, B00100010 }; // x
const PROGMEM byte char89[] = { 4, B00111001, B00000101, B00000101, B00111110            }; // y
const PROGMEM byte char90[] = { 3, B00100110, B00101010, B00110010                       }; // z
const PROGMEM byte char91[] = { 3, B00010000, B01101100, B10000010                       }; // {
const PROGMEM byte char92[] = { 1, B11111110                                             }; // |
const PROGMEM byte char93[] = { 3, B10000010, B01101100, B00010000                       }; // }
const PROGMEM byte char94[] = { 4, B00010000, B00100000, B00010000, B00100000            }; // ~  

#else

const PROGMEM byte char00[] = { 3, B00000000, B00000000, B00000000                       }; // space
const PROGMEM byte char01[] = { 1, B01011111                                             }; // !
const PROGMEM byte char02[] = { 3, B00000011, B00000000, B00000011                       }; // "
const PROGMEM byte char03[] = { 5, B00100100, B01111110, B00100100, B01111110, B00100100 }; // #
const PROGMEM byte char04[] = { 4, B00100100, B01101010, B00101011, B00010010            }; // $
const PROGMEM byte char05[] = { 5, B01100011, B00010011, B00001000, B01100100, B01100011 }; // %
const PROGMEM byte char06[] = { 5, B00110110, B01001001, B01010110, B00100000, B01010000 }; // &
const PROGMEM byte char07[] = { 1, B00000011                                             }; // '
const PROGMEM byte char08[] = { 3, B00011100, B00100010, B01000001                       }; // (
const PROGMEM byte char09[] = { 3, B01000001, B00100010, B00011100                       }; // )
const PROGMEM byte char10[] = { 5, B00101000, B00011000, B00001110, B00011000, B00101000 }; // *
const PROGMEM byte char11[] = { 5, B00001000, B00001000, B00111110, B00001000, B00001000 }; // +
const PROGMEM byte char12[] = { 2, B10110000, B01110000                                  }; // ,
const PROGMEM byte char13[] = { 4, B00001000, B00001000, B00001000, B00001000            }; // -
const PROGMEM byte char14[] = { 2, B01100000, B01100000                                  }; // .
const PROGMEM byte char15[] = { 4, B01100000, B00011000, B00000110, B00000001            }; // /
const PROGMEM byte char16[] = { 4, B00111110, B01000001, B01000001, B00111110            }; // 0
const PROGMEM byte char17[] = { 3, B01000010, B01111111, B01000000                       }; // 1
const PROGMEM byte char18[] = { 4, B01100010, B01010001, B01001001, B01000110            }; // 2
const PROGMEM byte char19[] = { 4, B00100010, B01000001, B01001001, B00110110            }; // 3
const PROGMEM byte char20[] = { 4, B00011000, B00010100, B00010010, B01111111            }; // 4
const PROGMEM byte char21[] = { 4, B00100111, B01000101, B01000101, B00111001            }; // 5
const PROGMEM byte char22[] = { 4, B00111110, B01001001, B01001001, B00110000            }; // 6
const PROGMEM byte char23[] = { 4, B01100001, B00010001, B00001001, B00000111            }; // 7
const PROGMEM byte char24[] = { 4, B00110110, B01001001, B01001001, B00110110            }; // 8
const PROGMEM byte char25[] = { 4, B00000110, B01001001, B01001001, B00111110            }; // 9
const PROGMEM byte char26[] = { 2, B01010000, B00000000                                  }; // :
const PROGMEM byte char27[] = { 2, B10000000, B01010000                                  }; // ;
const PROGMEM byte char28[] = { 3, B00010000, B00101000, B01000100                       }; // <
const PROGMEM byte char29[] = { 3, B00010100, B00010100, B00010100                       }; // =
const PROGMEM byte char30[] = { 3, B01000100, B00101000, B00010000                       }; // >
const PROGMEM byte char31[] = { 4, B00000010, B01011001, B00001001, B00000110            }; // ?
const PROGMEM byte char32[] = { 5, B00111110, B01001001, B01010101, B01011101, B00001110 }; // @
const PROGMEM byte char33[] = { 4, B01111110, B00010001, B00010001, B01111110            }; // A
const PROGMEM byte char34[] = { 4, B01111111, B01001001, B01001001, B00110110            }; // B
const PROGMEM byte char35[] = { 4, B00111110, B01000001, B01000001, B00100010            }; // C
const PROGMEM byte char36[] = { 4, B01111111, B01000001, B01000001, B00111110            }; // D
const PROGMEM byte char37[] = { 4, B01111111, B01001001, B01001001, B01000001            }; // E
const PROGMEM byte char38[] = { 4, B01111111, B00001001, B00001001, B00000001            }; // F
const PROGMEM byte char39[] = { 4, B00111110, B01000001, B01001001, B01111010            }; // G
const PROGMEM byte char40[] = { 4, B01111111, B00001000, B00001000, B01111111            }; // H
const PROGMEM byte char41[] = { 3, B01000001, B01111111, B01000001                       }; // I
const PROGMEM byte char42[] = { 4, B00110000, B01000000, B01000001, B00111111            }; // J
const PROGMEM byte char43[] = { 4, B01111111, B00001000, B00010100, B01100011            }; // K
const PROGMEM byte char44[] = { 4, B01111111, B01000000, B01000000, B01000000            }; // L
const PROGMEM byte char45[] = { 5, B01111111, B00000010, B00001100, B00000010, B01111111 }; // M
const PROGMEM byte char46[] = { 5, B01111111, B00000100, B00001000, B00010000, B01111111 }; // N
const PROGMEM byte char47[] = { 4, B00111110, B01000001, B01000001, B00111110            }; // O
const PROGMEM byte char48[] = { 4, B01111111, B00001001, B00001001, B00000110            }; // P
const PROGMEM byte char49[] = { 4, B00111110, B01000001, B01000001, B10111110            }; // Q
const PROGMEM byte char50[] = { 4, B01111111, B00001001, B00001001, B01110110            }; // R
const PROGMEM byte char51[] = { 4, B01000110, B01001001, B01001001, B00110010            }; // S
const PROGMEM byte char52[] = { 5, B00000001, B00000001, B01111111, B00000001, B00000001 }; // T
const PROGMEM byte char53[] = { 4, B00111111, B01000000, B01000000, B00111111            }; // U
const PROGMEM byte char54[] = { 5, B00001111, B00110000, B01000000, B00110000, B00001111 }; // V
const PROGMEM byte char55[] = { 5, B00111111, B01000000, B00111000, B01000000, B00111111 }; // W
const PROGMEM byte char56[] = { 5, B01100011, B00010100, B00001000, B00010100, B01100011 }; // X
const PROGMEM byte char57[] = { 5, B00000111, B00001000, B01110000, B00001000, B00000111 }; // Y
const PROGMEM byte char58[] = { 4, B01100001, B01010001, B01001001, B01000111            }; // Z
const PROGMEM byte char59[] = { 2, B01111111, B01000001                                  }; // [
const PROGMEM byte char60[] = { 4, B00000001, B00000110, B00011000, B01100000            }; // backslash
const PROGMEM byte char61[] = { 2, B01000001, B01111111, B00000000, B00000000            }; // ]
const PROGMEM byte char62[] = { 3, B00000010, B00000001, B00000010                       }; // ^
const PROGMEM byte char63[] = { 4, B01000000, B01000000, B01000000, B01000000            }; // _
const PROGMEM byte char64[] = { 2, B00000001, B00000010                                  }; // `
const PROGMEM byte char65[] = { 4, B00100000, B01010100, B01010100, B01111000            }; // a
const PROGMEM byte char66[] = { 4, B01111111, B01000100, B01000100, B00111000            }; // b
const PROGMEM byte char67[] = { 4, B00111000, B01000100, B01000100, B00101000            }; // c
const PROGMEM byte char68[] = { 4, B00111000, B01000100, B01000100, B01111111            }; // d
const PROGMEM byte char69[] = { 4, B00111000, B01010100, B01010100, B00011000            }; // e
const PROGMEM byte char70[] = { 3, B00000100, B01111110, B00000101                       }; // f
const PROGMEM byte char71[] = { 4, B10011000, B10100100, B10100100, B01111000            }; // g
const PROGMEM byte char72[] = { 4, B01111111, B00000100, B00000100, B01111000            }; // h
const PROGMEM byte char73[] = { 3, B01000100, B01111101, B01000000                       }; // i
const PROGMEM byte char74[] = { 4, B01000000, B10000000, B10000100, B01111101            }; // j
const PROGMEM byte char75[] = { 4, B01111111, B00010000, B00101000, B01000100            }; // k
const PROGMEM byte char76[] = { 3, B01000001, B01111111, B01000000                       }; // l
const PROGMEM byte char77[] = { 5, B01111100, B00000100, B01111100, B00000100, B01111000 }; // m
const PROGMEM byte char78[] = { 4, B01111100, B00000100, B00000100, B01111000            }; // n
const PROGMEM byte char79[] = { 4, B00111000, B01000100, B01000100, B00111000            }; // o
const PROGMEM byte char80[] = { 4, B11111100, B00100100, B00100100, B00011000            }; // p
const PROGMEM byte char81[] = { 4, B00011000, B00100100, B00100100, B11111100            }; // q
const PROGMEM byte char82[] = { 4, B01111100, B00001000, B00000100, B00000100            }; // r
const PROGMEM byte char83[] = { 4, B01001000, B01010100, B01010100, B00100100            }; // s
const PROGMEM byte char84[] = { 3, B00000100, B00111111, B01000100                       }; // t
const PROGMEM byte char85[] = { 4, B00111100, B01000000, B01000000, B01111100            }; // u
const PROGMEM byte char86[] = { 5, B00011100, B00100000, B01000000, B00100000, B00011100 }; // v
const PROGMEM byte char87[] = { 5, B00111100, B01000000, B00111100, B01000000, B00111100 }; // w
const PROGMEM byte char88[] = { 5, B01000100, B00101000, B00010000, B00101000, B01000100 }; // x
const PROGMEM byte char89[] = { 4, B10011100, B10100000, B10100000, B01111100            }; // y
const PROGMEM byte char90[] = { 3, B01100100, B01010100, B01001100                       }; // z
const PROGMEM byte char91[] = { 3, B00001000, B00110110, B01000001                       }; // {
const PROGMEM byte char92[] = { 1, B01111111                                             }; // |
const PROGMEM byte char93[] = { 3, B01000001, B00110110, B00001000                       }; // }
const PROGMEM byte char94[] = { 4, B00001000, B00000100, B00001000, B00000100            }; // ~  

#endif

const PROGMEM  byte* const ASCII[] = { 
  char00, char01, char02, char03, char04, char05, char06, char07, char08, char09, 
  char10, char11, char12, char13, char14, char15, char16, char17, char18, char19, 
  char20, char21, char22, char23, char24, char25, char26, char27, char28, char29, 
  char30, char31, char32, char33, char34, char35, char36, char37, char38, char39, 
  char40, char41, char42, char43, char44, char45, char46, char47, char48, char49, 
  char50, char51, char52, char53, char54, char55, char56, char57, char58, char59, 
  char60, char61, char62, char63, char64, char65, char66, char67, char68, char69, 
  char70, char71, char72, char73, char74, char75, char76, char77, char78, char79, 
  char80, char81, char82, char83, char84, char85, char86, char87, char88, char89, 
  char90, char91, char92, char93, char94
};

class TextASCII {
	public:
		TextASCII(LedControl *lc);

		// Copy the display data for the specified character into the given location
		// If your LED matrices have their columns oriented vertically, do #define TEXTASCII_COLS
		// before including this library.
		int copyChar(byte* dst, char c);

		// Scroll text across an LED display made of 8x8 matrices. Uses LedControl library to control the matrices

		// Initialise scrolling
		// txtBuf - location of the text
		// txtLen - how many characters of text
		void scrollInit(char *txtBuf, int txtLen);

		// Scroll the text one step
		void scroll();
		
		// Stop scrolling and clear the displays
		void clear();

        // Check whether scrolling is in progress		
		bool isScrolling();
		
		// Check whether a character can be displayed
		bool inRange(char c);
	private:
		void refreshDisplay();
		byte _colCount[1];
		byte _dispBuf[64];
		int _dispBufLen, _remainingBytes;
		int _txtLen, _txtIdx, _charLen, _charIdx;
		char *_txtBuf;
		LedControl *_lc;
		byte _charBuf[6]; // storage for the next character
		byte _offset;
};

#endif //TEXTASCII_H