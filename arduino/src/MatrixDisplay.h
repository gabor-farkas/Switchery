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

struct DisplayData {
	byte * imageBuffer;
	byte digits[4] = {};
	word leds;
};

/**
 * There are the following display elements in the board:
 *   - a 32x8 matrix with integrated everything, controlled by 4 serially connected MAX7219 chips
 *   - a 4x(7+1) segment display
 *   - 12 LEDs
 * The segment display and the 12 LEDs are controlled by an additional MAX7219 connected in serial with the 32x8 matrix display,
 * which controls 8x8 leds. The 7-segment decode function is not used. The first 4 digits control the segmented display,
 * digit 4 controls the left 8 LEDs, and part of digit 5 controls the 4 other LEDs. The central 4 leds are bridged to the right 4.
 * 
 * The wiring follows the IC pinout:
 *   * 23, seg D,  led 0            | bit 3
 *   * 22, seg DP, led 1            | bit 7
 *   * 21, seg E,  led 2            | bit 2
 *   * 20, seg C,  led 3            | bit 4
 *   * 17, seg G,  led 4 - led 8    | bit 0
 *   * 16, seg B,  led 5 - led 9    | bit 5
 *   * 15, seg F,  led 6 - led 10   | bit 1
 *   * 14, seg A,  led 7 - led 11   | bit 6
 * 
 * The internal wiring of MAX7219 assigns register bits in the following order:
 *   (D7 -> D0) -> (DP, A, B, C, D, E, F, G)
 * Thus the bit mapping in the table above. The seg G-B-F-A of digit 5 controls the right 4 leds.
 * 
 */  
class MatrixDisplay {
private:
	DisplayData displayData;
	void loadCommands(word command0, word command1, word command2, word command3, word command4);
	void writeRegisterSame(word address, word value);
	void resetOperation();
	byte translateLedBits(byte input);
public:
	void setup();
	void writeRegisters(word address, word value0, word value1, word value2, word value3, word value4);
	void clear();
	DisplayData * getDisplayData();
	void draw();
};


#endif

