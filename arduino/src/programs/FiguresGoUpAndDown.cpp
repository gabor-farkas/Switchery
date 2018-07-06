#include "FiguresGoUpAndDown.h"
#include "../Images.h"

FiguresGoUpAndDown::FiguresGoUpAndDown(Board * board) {
    this->board = board;
    figure2.position = 24;
}

void FiguresGoUpAndDown::loop() {
    short charCode = board->getLastCharacter();
    DisplayData * displayData = board->getMatrixDisplay()->getDisplayData();
    if (charCode != -1) {
        Figure * controlledFigure = 0;
        if (charCode >> 4 == NL) {
            controlledFigure = &figure1;
        }
        if (charCode >> 4 == NR) {
            controlledFigure = &figure2;
        }
        if (controlledFigure != 0) {
            byte subCode = charCode & 0xF;
            if (subCode == 4) {
                controlledFigure->position = (controlledFigure->position - 1) & 31;
            } else if (subCode == 6) {
                controlledFigure->position = (controlledFigure->position + 1) & 31;
            } else if (subCode == 0xA) {
                controlledFigure->code = (controlledFigure->code + 1) & 7;
            }
        }
    }
    board->getCharacters()->draw(displayData->imageBuffer, (byte* )&LEDMAP_IMAGES, 8, 8, figure1.code, figure1.position, 0);
    if (figure1.position > 24) {
        board->getCharacters()->draw(displayData->imageBuffer, (byte* )&LEDMAP_IMAGES, 8, 8, figure1.code, figure1.position - 32, 0);
    }
    board->getCharacters()->draw(displayData->imageBuffer, (byte* )&LEDMAP_IMAGES, 8, 8, figure2.code, figure2.position, 0);
    if (figure2.position > 24) {
        board->getCharacters()->draw(displayData->imageBuffer, (byte* )&LEDMAP_IMAGES, 8, 8, figure2.code, figure2.position - 32, 0);
    }
}