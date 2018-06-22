#include "MatrixDisplay.h"
#include "Buttons.h"
#include "Characters.h";


MatrixDisplay * matrixDisplay;
Buttons * buttons;
Characters * characters;


void setup()
{
	matrixDisplay = new MatrixDisplay();
	buttons = new Buttons();
	characters = new Characters();

	matrixDisplay->setup();
	buttons->setup();
}

short x = 10;
short y = 4;
byte num = 0;
int counter = 0;

void drawScene() {
	short byteX = x / 8;
	short bitX = 1 << (x % 8);
	matrixDisplay->clear();
	byte * imageBuffer = matrixDisplay->getImageBuffer();
	imageBuffer[y * 4 + byteX] |= bitX;
	byte charX = (counter / 2) & 31;
	byte lowCount = (counter / 4) & 7;
	for (int i = 0; i < 8; i ++) {
		imageBuffer[i*4] |= (1 << lowCount);
	}
	characters->draw(imageBuffer, (byte *)(&NUMBERS), 5, 3, num, charX, 1);
	matrixDisplay->draw();
}


void loop()
{
	Serial.begin(9600);
	while (true) {
		delay(100);
		x = (x+1) & 31;
		y = round((sin((counter++) / 10.0) * 3.5 + 3.5));
		drawScene();
		short charCode = buttons->read();
		if (charCode != -1) {
			Serial.printf("%04x\n", charCode);
			if (charCode >> 4 == NL) {
				num = charCode & 0xF;
			}
		}
		/*
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
		*/
	}
}
