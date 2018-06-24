#include "board.h"

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