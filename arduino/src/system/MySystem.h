#pragma once
#include <Arduino.h>

class TimerCallback {
    public:
        virtual void timerCallback() = 0;
};

class MySystem {
    private:
        struct TimerRegistration {
            short intervalMs;
            short countDownMs;
            TimerCallback * timerCallback;
        };
        TimerRegistration timerRegistrations[16];
        int numberOfTimerRegistrations = 0;
    public:
        String * timeString = new String("");
        void registerTimer(short intervalMs, TimerCallback * timerCallback);
        void tick(short timePassedMs);
};