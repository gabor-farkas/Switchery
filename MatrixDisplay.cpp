// 
// 
// 

#include "MatrixDisplay.h"


void MatrixDisplay::setup() {
	pinMode(LED_CS, OUTPUT);
	pinMode(LED_CLK, OUTPUT);
	pinMode(LED_DIN, OUTPUT);
	digitalWrite(LED_CS, HIGH);
	pinMode(LED_BUILTIN, OUTPUT);
	//
	writeRegisterSame(15, 0x0);
	writeRegisterSame(9, 0x0);
	writeRegisterSame(0xA, 0x0);
	writeRegisterSame(0xB, 0x7);
	writeRegisterSame(0xC, 0x1);
}

void MatrixDisplay::loadCommands(word command0, word command1, word command2, word command3) {
	digitalWrite(LED_CS, HIGH);
	digitalWrite(LED_CLK, LOW);
	digitalWrite(LED_DIN, LOW);
	delayMicroseconds(1);
	digitalWrite(LED_CS, LOW);
	word commands[] = { command3, command2, command1, command0 };
	for (short c = 0; c < 4; c++) {
		for (short i = 0; i < 16; i++) {
			//delayMicroseconds(1);
			digitalWrite(LED_DIN, (commands[c] & 0x8000) ? HIGH : LOW);
			commands[c] = commands[c] << 1;
			digitalWrite(LED_CLK, HIGH);
			//delayMicroseconds(1);
			digitalWrite(LED_CLK, LOW);
		}
	}
	digitalWrite(LED_CS, HIGH);
	delayMicroseconds(1);
}

void MatrixDisplay::writeRegisterSame(short address, short value) {
	word command = (address << 8) + value;
	loadCommands(command, command, command, command);
}

void MatrixDisplay::writeRegisters(short address, short value0, short value1, short value2, short value3) {
	loadCommands((address << 8) + value0, (address << 8) + value1, (address << 8) + value2, (address << 8) + value3);
}
