#pragma once
#include <Arduino.h>

const byte NUMBERS[] = {
	// 0
	0b010,
	0b101,
	0b101,
	0b101,
	0b010,
	// 1
	0b001,
	0b011,
	0b001,
	0b001,
	0b001,
	// 2
	0b111,
	0b001,
	0b111,
	0b100,
	0b111,
	// 3
	0b111,
	0b001,
	0b111,
	0b001,
	0b111,
	// 4
	0b101,
	0b101,
	0b111,
	0b001,
	0b001,
	// 5
	0b111,
	0b100,
	0b111,
	0b001,
	0b111,
	// 6
	0b111,
	0b100,
	0b111,
	0b101,
	0b111,
	// 7
	0b111,
	0b001,
	0b001,
	0b001,
	0b001,
	// 8
	0b111,
	0b101,
	0b111,
	0b101,
	0b111,
	// 9
	0b111,
	0b101,
	0b111,
	0b001,
	0b001,
	// A
	0b010,
	0b101,
	0b111,
	0b101,
	0b101,
	// B
	0b110,
	0b101,
	0b110,
	0b101,
	0b110
};

class Characters {
public:
	/**
	 * draws on the given 32x8 canvas, uses the patterns array (eg NUMBERS above), and draws characterCode (offsetting the patterns array),
	 * and position targetX-targetY
	*/
	void draw(byte * canvas, byte * patterns, byte patternHeight, byte patternWidth, short characterCode, byte targetX, byte targetY);
};