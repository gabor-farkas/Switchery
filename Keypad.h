// Keypad.h

#ifndef _KEYPAD_h
#define _KEYPAD_h

#define NP_COL1 0
#define NP_COL2 1
#define NP_COL3 2
#define NP_ROW1 3
#define NP_ROW2 4
#define NP_ROW3 5
#define NP_ROW4 6

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Keypad {
private:
	short lastCharCode = -1;
public:
	void setup();
	short readChar();
};



#endif

