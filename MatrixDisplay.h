// MatrixDisplay.h

#ifndef _MATRIXDISPLAY_h
#define _MATRIXDISPLAY_h

#define LED_DIN 12 // D6
#define LED_CS 13  // D7
#define LED_CLK 15  // D8

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MatrixDisplay {
private:
	byte* imageBuffer;
	void loadCommands(word command0, word command1, word command2, word command3);
	void writeRegisterSame(short address, short value);
public:
	void setup();
	void writeRegisters(short address, short value0, short value1, short value2, short value3);
	void clear();
	byte * getImageBuffer();
	void draw();
};


#endif

