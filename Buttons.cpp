#include "Wire.h"
#include "Buttons.h"
#include "mux.h"

void Buttons::setup() {
	Wire.begin();
	mux->write(0x05, 0b0010000); // force bank to 0
	mux->write(0x0A, 0b0010000); // IOCON bank=0, seqop disabled
	mux->write(0x00, 0x0F); // A0-A3 as inputs, A4-A7 as outputs
	mux->write(0x01, 0x00); // B0-B7 as outputs
	mux->write(0x0C, 0xFF); // pullup on A
	mux->write(0x0D, 0xFF); // pullup on B
	mux->write(0x12, 0xF0); // output on A
	mux->write(0x13, 0xFF); // output on B
}

short Buttons::read() {
	short pressedButton = -1;
	for (int i = 0; i < 12; i++) {
		short mask = ~((short) 0x10 << i);
		byte maskA = mask & 0xFF;
		byte maskB = (mask >> 8) & 0xFF;
		mux->write(0x12, maskA);
		mux->write(0x13, maskB);
		byte portAValue = mux->read(0x12) & 0x0F;
		byte downEdges = (previousButtonState[i] ^ portAValue) & portAValue;
		previousButtonState[i] = portAValue;
		if (downEdges != 0) {
			byte subIndex = downEdges >= 8 ? 3 : (downEdges >= 4 ? 2 : (downEdges >=2 ? 1 : 0));
			byte buttonGroup = buttonGroupDecode[i];
			pressedButton = buttonGroup << 4;
			switch (buttonGroup) {
				case PL:
					pressedButton |= subIndex * 2 + i;
					break;
				case NL: {
					byte rowIndex = i - 4;
					byte numCode = subIndex * 3 + rowIndex + 1;
					if (numCode == 11) numCode = 0;
					if (numCode == 12) numCode = 11;
					pressedButton |= numCode;
					break;
				}
			}
		}
		mux->write(0x12, 0xF0);
		mux->write(0x13, 0xFF);
	}
	return pressedButton;
}
