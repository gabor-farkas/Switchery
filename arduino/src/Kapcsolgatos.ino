#include "Board.h"
#include "Characters.h"
#include "programs/FourDigits.h"
#include "programs/ImagePad.h"
#include "programs/SegmentSwitcher.h"

Board * board;
Characters * characters;

void setup()
{
	board = new Board();
	characters = new Characters();

	board->setup();
}

void loop()
{
	Serial.begin(9600);
	FourDigits * p = new FourDigits(board);
	ImagePad * ip = new ImagePad(board);
	SegmentSwitcher * ss = new SegmentSwitcher(board);
	while (true) {
		delay(25);
		board->readChar();
		board->getMatrixDisplay()->clear();
		p->loop();
		ip->loop();
		ss->loop();
		board->getMatrixDisplay()->draw();
	}
}
