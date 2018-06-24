#include "Board.h"
#include "Characters.h"
#include "programs/FourDigits.h"
#include "programs/ImagePad.h"

Board * board;
Characters * characters;

void setup()
{
	board = new Board();
	characters = new Characters();

	board->setup();
}

short x = 10;
short y = 4;
byte num = 0;
int counter = 0;

void drawScene() {
	short byteX = x / 8;
	short bitX = 1 << (x % 8);
	board->getMatrixDisplay()->clear();
	byte * imageBuffer = board->getMatrixDisplay()->getImageBuffer();
	imageBuffer[y * 4 + byteX] |= bitX;
	byte charX = (counter / 2) & 31;
	byte lowCount = (counter / 4) & 7;
	for (int i = 0; i < 8; i ++) {
		imageBuffer[i*4] |= (1 << lowCount);
	}
	characters->draw(imageBuffer, (byte *)(&NUMBERS), 5, 3, num, charX, 1);
	board->getMatrixDisplay()->draw();
}


void loop()
{
	Serial.begin(9600);
	FourDigits * p = new FourDigits(board);
	ImagePad * ip = new ImagePad(board);
	while (true) {
		delay(25);
		board->readChar();
		board->getMatrixDisplay()->clear();
		p->loop();
		ip->loop();
		board->getMatrixDisplay()->draw();
		x = (x+1) & 31;
		y = round((sin((counter++) / 10.0) * 3.5 + 3.5));
		//drawScene();
		/*
		short charCode = board->getButtons()->read();
		if (charCode != -1) {
			Serial.printf("%04x\n", charCode);
			if (charCode >> 4 == NL) {
				num = charCode & 0xF;
			}
		}
		*/
	}
}
