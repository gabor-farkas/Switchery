// 
// 
// 

#include "Keypad.h"

void Keypad::setup() {
	pinMode(NP_COL1, OUTPUT);
	pinMode(NP_COL2, OUTPUT);
	pinMode(NP_COL3, OUTPUT);
	pinMode(NP_ROW1, INPUT_PULLUP);
	pinMode(NP_ROW2, INPUT_PULLUP);
	pinMode(NP_ROW3, INPUT_PULLUP);
	pinMode(NP_ROW4, INPUT_PULLUP);
	digitalWrite(NP_COL1, HIGH);
	digitalWrite(NP_COL2, HIGH);
	digitalWrite(NP_COL3, HIGH);
}

short Keypad::readChar() {
	short cols[] = { NP_COL1, NP_COL2, NP_COL3 };
	short rows[] = { NP_ROW1, NP_ROW2, NP_ROW3, NP_ROW4 };
	// scan through cols
	short keyCode = -1;
	for (short col = 0; col < 3; col++) {
		digitalWrite(cols[col], LOW);
		// read throgh rows
		for (short row = 0; row < 4; row++) {
			short keyValue = digitalRead(rows[row]);
			if (keyValue == LOW) {
				keyCode = row * 3 + col + 1;
			}
		}
		digitalWrite(cols[col], HIGH);
	}
	if (lastCharCode == keyCode) {
		// key already processed
		return -1;
	}
	lastCharCode = keyCode;
	return keyCode;
}

