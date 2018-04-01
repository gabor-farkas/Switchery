#include "MatrixDisplay.h"
#include "Keypad.h"


MatrixDisplay * matrixDisplay;
Keypad * keypad;

void setup()
{
	matrixDisplay = new MatrixDisplay();
	keypad = new Keypad();

	matrixDisplay->setup();
	keypad->setup();
}

short image2[] =
{ 0b00000000, 0b00000000, 0b00000000, 0b00000000,
0b00000000, 0b00000000, 0b00000000, 0b00000000,
0b00000000, 0b00000000, 0b00000000, 0b00000000,
0b00000000, 0b00000000, 0b00000000, 0b00000000,
0b00000000, 0b00000000, 0b00000000, 0b00000000,
0b00000000, 0b00000000, 0b00000000, 0b00000000,
0b00000000, 0b00000000, 0b00000000, 0b00000000,
0b00000000, 0b00000000, 0b00000000, 0b00000000 };


short x = 10;
short y = 4;
void drawScene() {
	short byteX = x / 8;
	short bitX = 1 << (x % 8);
	for (short i = 0; i < 8 * 4; i++) {
		image2[i] = 0;
	}
	image2[y * 4 + byteX] |= bitX;
	for (int i = 0; i < 8; i++) {
		matrixDisplay->writeRegisters(8 - i, image2[i * 4], image2[i * 4 + 1], image2[i * 4 + 2], image2[i * 4 + 3]);
	}
}


void loop()
{
	while (true) {
		delay(10);
		short charCode = keypad->readChar();
		if (charCode != -1) {
			if (charCode == 4) {
				x--;
			}
			if (charCode == 6) {
				x++;
			}
			if (charCode == 2) {
				y--;
			}
			if (charCode == 8) {
				y++;
			}
			drawScene();
		}
	}
}
