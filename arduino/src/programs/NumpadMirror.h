#pragma once
#include "../Board.h"

class NumpadMirror {
    Board * board;
    public:
        NumpadMirror(Board * board);
        void loop();
};