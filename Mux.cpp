#include "Wire.h"
#include "Mux.h";

void Multiplexer::write(byte address, byte data) {
	Wire.beginTransmission(0x20);
	Wire.write(address);
	Wire.write(data);
	Wire.endTransmission();
}

short Multiplexer::read(byte address) {
	Wire.beginTransmission(0x20);
	Wire.write(address);
	Wire.endTransmission();
	Wire.requestFrom(0x20, 1);
	return Wire.read();
}
