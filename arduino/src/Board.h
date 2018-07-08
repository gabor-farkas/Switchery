#pragma once
#include "MatrixDisplay.h"
#include "Buttons.h"
#include "Characters.h"
#include "system/MySystem.h"

class Board
{
  private:
    MatrixDisplay *matrixDisplay;
    Buttons *buttons;
    Characters *characters;
    short lastCharacter;
  public:
    MySystem * mySystem;
    Board(MySystem * mySystem);
    void setup();
    MatrixDisplay *getMatrixDisplay();
    Buttons *getButtons();
    Characters *getCharacters();
    void readChar();
    short getLastCharacter();
    /**
     * Plays a tone, with respect to the normal 8am-8pm time range
     */ 
    void playTone(int frequency, int durationMs);
};