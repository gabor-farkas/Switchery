// 
// 
// 

#include "MatrixDisplay.h"

const byte ledBitTranslationTable[8] = {0x08, 0x80, 0x04, 0x10, 0x01, 0x20, 0x02, 0x40};

const byte digitSegments[] = {
	0b1111110,
	0b0110000,
	0b1101101,
	0b1111001,
	0b0110011,
	0b1011011,
	0b1011111,
	0b1110000,
	0b1111111,
	0b1111011
};

void MatrixDisplay::setup() {
	pinMode(LED_CS, OUTPUT);
	pinMode(LED_CLK, OUTPUT);
	pinMode(LED_DIN, OUTPUT);
	digitalWrite(LED_CS, HIGH);
	pinMode(LED_BUILTIN, OUTPUT);
	displayData.imageBuffer = (byte*) malloc(4*8);
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
		displayData.imageBuffer[i] = 0;
	}
}

DisplayData * MatrixDisplay::getDisplayData() {
	return &displayData;
}

byte MatrixDisplay::translateLedBits(byte input) {
	byte result = 0;
	for (int i = 0; i < 8; i ++) {
		result |= ledBitTranslationTable[i] * (input & 1);
		input >>= 1;
	}
	return result;
}

void MatrixDisplay::draw() {
	byte * img = displayData.imageBuffer;
	byte specials [] = {displayData.digits[0], displayData.digits[1], displayData.digits[2], displayData.digits[3],
						translateLedBits(displayData.leds & 0xFF), translateLedBits(((displayData.leds >> 8) & 0x0F) << 4), 0, 0};
	for (int i = 0; i < 8; i++) {
		writeRegisters(8 - i, img[i * 4] , img[i * 4 + 1], img[i * 4 + 2], img[i * 4 + 3], specials[7-i]);
	}
}

void MatrixDisplay::setDigits(String * digits) {
	unsigned int digitCount = 0;
	unsigned int index = 0;
	do {
		char chr = digits->charAt(index);
		if (chr >= '0' && chr <= '9') {
			displayData.digits[digitCount] = digitSegments[chr - '0'];
			digitCount ++;
		} else if (chr == '.') {
			if (digitCount > 0) {
				displayData.digits[digitCount-1] |= 0x80;
			}
		}
		index ++;
	} while (digitCount < 4 && digits->length() > index);
}