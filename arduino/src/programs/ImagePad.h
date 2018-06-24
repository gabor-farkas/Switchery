#pragma once
#include "../Board.h"

class ImagePad {
    Board * board;
    byte images [2] = {0, 0};
    byte cursor = 0;
    public:
        ImagePad(Board * board);
        void loop();
};