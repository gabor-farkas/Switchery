#include "system/MySystem.h"
#include "connect/ConnectionManager.h"
#include "Board.h"
#include "Characters.h"
#include "programs/FourDigits.h"
//#include "programs/ImagePad.h"
#include "programs/SegmentSwitcher.h"
#include "programs/FiguresGoUpAndDown.h"
#include "programs/MiniPiano.h"

MySystem * mySystem;
ConnectionManager * connections;
Board * board;
Characters * characters;

void setup()
{
	mySystem = new MySystem();
	connections = new ConnectionManager(mySystem);
	board = new Board();
	characters = new Characters();

	board->setup();
}

void loop()
{
	Serial.begin(9600);
	//FourDigits * p = new FourDigits(board);
	//ImagePad * ip = new ImagePad(board);
	SegmentSwitcher * ss = new SegmentSwitcher(board);
	FiguresGoUpAndDown * figures = new FiguresGoUpAndDown(board);
	MiniPiano * miniPiano = new MiniPiano(board);
	while (true) {
		delay(25);
		mySystem->tick(25);
		board->readChar();
		short lastChar = board->getLastCharacter();
		if (lastChar != -1) {
			Serial.println(board->getLastCharacter());
		}
		board->getMatrixDisplay()->clear();
		//p->loop();
		//ip->loop();
		ss->loop();
		figures->loop();
		miniPiano->loop();
		board->getMatrixDisplay()->draw();
	}
}
