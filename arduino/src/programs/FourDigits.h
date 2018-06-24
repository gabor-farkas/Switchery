#pragma once
#include "../Board.h"

class FourDigits {
    Board * board;
    byte digits [4] = {0, 0, 0, 0};
    byte cursor = 0;
    public:
        FourDigits(Board * board);
        void loop();
};