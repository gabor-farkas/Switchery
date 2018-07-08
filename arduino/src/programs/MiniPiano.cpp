#include <Arduino.h>
#include "MiniPiano.h"

MiniPiano::MiniPiano(Board *board)
{
    this->board = board;
}

const float C4 = 261.63f;
const float singleNoteMultiplier = pow(2, 1.0f/12);
const int cMajorScale[7] = {0, 2, 4, 5, 7, 9, 11};

void MiniPiano::loop()
{
    short charCode = board->getLastCharacter();
    if (charCode != -1)
    {
        int groupCode = charCode >> 4;
        if (groupCode == NL || groupCode == NR) {
            byte subCode = charCode & 0xF;
            int note  = subCode - 1;
            int subNote = note  % 7;
            int octaveOffset = note / 7;
            if (groupCode == NR) octaveOffset ++;
            float freq = C4 * (1 << octaveOffset) * pow(singleNoteMultiplier, cMajorScale[subNote]);
            board->playTone( floor(freq), 250);
        }
    }
}