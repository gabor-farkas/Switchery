#pragma once
#include "../system/MySystem.h"

class TimeSynchronizer: public TimerCallback {
    private:
        int refetchCountDown = 0;
        void syncTime();
        MySystem * mySystem;
    public:
        TimeSynchronizer(MySystem * mySystem);
        virtual void timerCallback();
};