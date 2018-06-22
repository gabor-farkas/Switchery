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
	imageBuffer = (byte*) malloc(4*8);
	//
	resetOperation();
}

void MatrixDisplay::resetOperation() {
	writeRegisterSame(0xF, 0x0); // no test mode
	writeRegisterSame(0x9, 0x0); // no decode
	writeRegisters(0xA, 0x0, 0x0, 0x0, 0x0, 0x8	); // intensity lowest
	writeRegisterSame(0xB, 0x7); // scan limit -> all digits
	writeRegisterSame(0xC, 0x1); // shutdown register -> normal operation
}

void MatrixDisplay::loadCommands(word command0, word command1, word command2, word command3, word command4) {
	digitalWrite(LED_CS, HIGH);
	digitalWrite(LED_CLK, LOW);
	digitalWrite(LED_DIN, LOW);
	delayMicroseconds(1);
	digitalWrite(LED_CS, LOW);
	delayMicroseconds(10);
	word commands[] = { command4, command3, command2, command1, command0 };
	for (short c = 0; c < 5; c++) {
		for (short i = 0; i < 16; i++) {
			digitalWrite(LED_CLK, LOW);
			delayMicroseconds(1);
			digitalWrite(LED_DIN, (commands[c] & 0x8000) ? HIGH : LOW);
			delayMicroseconds(1);
			commands[c] = commands[c] << 1;
			digitalWrite(LED_CLK, HIGH);
			delayMicroseconds(1);
		}
	}
	delayMicroseconds(10);
	digitalWrite(LED_CS, HIGH);
	delayMicroseconds(1);
}

void MatrixDisplay::writeRegisterSame(word address, word value) {
	word command = (address << 8) | value;
	loadCommands(command, command, command, command, command);
}

void MatrixDisplay::writeRegisters(word address, word value0, word value1, word value2, word value3, word value4) {
	loadCommands((address << 8) | value0, (address << 8) | value1, (address << 8) | value2, (address << 8) | value3, (address << 8) | value4);
}

void MatrixDisplay::clear() {
	for (short i = 0; i < 8 * 4; i++) {
		imageBuffer[i] = 0;
	}
}

byte * MatrixDisplay::getImageBuffer() {
	return imageBuffer;
}

void MatrixDisplay::draw() {
	resetOperation();
	for (int i = 0; i < 8; i++) {
		writeRegisters(8 - i, imageBuffer[i * 4] , imageBuffer[i * 4 + 1], imageBuffer[i * 4 + 2], imageBuffer[i * 4 + 3], imageBuffer[i * 4]);
	}
}
