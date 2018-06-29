#include "SegmentSwitcher.h"

SegmentSwitcher::SegmentSwitcher(Board * board) {
    this->board = board;
}

void SegmentSwitcher::loop() {
    short charCode = board->getLastCharacter();
    DisplayData * displayData = board->getMatrixDisplay()->getDisplayData();
    if (charCode != -1) {
        byte subCode = charCode & 0xF;
        if (charCode >> 4 == PL) {
            if (subCode == 7) {
                cursor = (cursor + 1) & 3;
            } else {
                displayData->digits[cursor] ^= (1 << subCode);
            }
        }
        if (charCode >> 4 == PR) {
            if (subCode == 7) {
                displayData->leds = 0;
            }
            if (subCode >= 4 && subCode < 7) {
                ledCursor = subCode - 4;
            }
            if (subCode < 4) {
                displayData->leds ^= (1 << subCode) << (ledCursor * 4);
            }
        }
    }
}