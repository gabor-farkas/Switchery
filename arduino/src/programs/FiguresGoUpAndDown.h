#pragma once
#include "../Board.h"

struct Figure {
    byte code = 0;
    byte position = 0;
};

class FiguresGoUpAndDown {
    Board * board;
    Figure figure1;
    Figure figure2;
    public:
        FiguresGoUpAndDown(Board * board);
        void loop();
};