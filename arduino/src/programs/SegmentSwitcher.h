#pragma once
#include "../Board.h"

class SegmentSwitcher {
    Board * board;
    byte cursor = 0;
    byte ledCursor = 0;
    public:
        SegmentSwitcher(Board * board);
        void loop();
};