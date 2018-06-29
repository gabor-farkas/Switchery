#pragma once
#include "MatrixDisplay.h"
#include "Buttons.h"
#include "Characters.h"

class Board
{
  private:
    MatrixDisplay *matrixDisplay;
    Buttons *buttons;
    Characters *characters;
    short lastCharacter;

  public:
    void setup();
    MatrixDisplay *getMatrixDisplay();
    Buttons *getButtons();
    Characters *getCharacters();
    void readChar();
    short getLastCharacter();
};