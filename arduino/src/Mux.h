#pragma once
#include <Arduino.h>

class Multiplexer {
public:
	void write(byte, byte);
	short read(byte);
};
