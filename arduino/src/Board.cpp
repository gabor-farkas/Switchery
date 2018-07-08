#include "board.h"

Board::Board(MySystem * mySystem) {
    this->mySystem = mySystem;
}

void Board::setup() {
    matrixDisplay = new MatrixDisplay();
    buttons = new Buttons();
    characters = new Characters();
   	matrixDisplay->setup();
	buttons->setup();
}

MatrixDisplay * Board::getMatrixDisplay() {
    return matrixDisplay;
}

Buttons * Board::getButtons() {
    return buttons;
}

Characters * Board::getCharacters() {
    return characters;
}

void Board::readChar() {
    lastCharacter = buttons->read();
}

short Board::getLastCharacter() {
    return lastCharacter;
}

void Board::playTone(int frequency, int durationMs) {
    if (mySystem->timeString->compareTo("0800") > 0 && mySystem->timeString->compareTo("2000") < 0) {
        tone(14, frequency, durationMs);
    }
}