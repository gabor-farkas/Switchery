#include "NumpadMirror.h"

NumpadMirror::NumpadMirror(Board * board) {
    this->board = board;
}

void NumpadMirror::loop() {
    short charCode = board->getButtons()->read();
    if (charCode != -1) {
        if (charCode >> 4 == NL) {
            Serial.printf("%04x\n", charCode);
        }
    }
}