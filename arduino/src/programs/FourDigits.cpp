#include "FourDigits.h"
#include "../Characters.h";

FourDigits::FourDigits(Board * board) {
    this->board = board;
}

void FourDigits::loop() {
    short charCode = board->getLastCharacter();
    if (charCode != -1) {
        if (charCode >> 4 == NR) {
            byte subCode = charCode & 0xF;
            digits[cursor] = subCode;
            cursor = (cursor + 1) & 3;
        }
    }
    byte * buffer = board->getMatrixDisplay()->getImageBuffer();
    for (int i = 0; i < 4; i ++) {
        board->getCharacters()->draw(buffer, (byte *)&NUMBERS, 5, 3, digits[i], 16 + i * 4, 2);
    }
}