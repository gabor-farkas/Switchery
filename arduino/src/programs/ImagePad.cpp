#include "ImagePad.h"
#include "../Characters.h";
#include "../Images.h";

ImagePad::ImagePad(Board * board) {
    this->board = board;
}

void ImagePad::loop() {
    short charCode = board->getLastCharacter();
    if (charCode != -1) {
        if (charCode >> 4 == NL) {
            byte subCode = charCode & 0xF;
            images[cursor] = subCode % 8;
            cursor = (cursor + 1) & 1;
        }
    }
    byte * buffer = board->getMatrixDisplay()->getImageBuffer();
    for (int i = 0; i < 2; i ++) {
        board->getCharacters()->draw(buffer, (byte *)&LEDMAP_IMAGES, 8, 8, images[i], i * 8, 0);
    }
}