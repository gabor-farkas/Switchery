#pragma once
#include "../Board.h"

class MiniPiano {
    Board * board;
    public:
        MiniPiano(Board * board);
        void loop();
};
