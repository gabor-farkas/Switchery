#pragma once
#include "../system/MySystem.h"

class ConnectionManager: public TimerCallback {
    private:
        int waitCounter = 0;
        void reconnectWifi();
    public:
        ConnectionManager(MySystem * mySystem);
        void init();
        void regularCheck();
        virtual void timerCallback();
};