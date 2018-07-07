#include <Arduino.h>
#include "MySystem.h"

void MySystem::registerTimer(short intervalMs, TimerCallback * timerCallback) {
    if (numberOfTimerRegistrations == 15) {
        Serial.println("Can't register more timers than 16");
    }
    TimerRegistration * registration = &timerRegistrations[numberOfTimerRegistrations];
    registration->countDownMs = intervalMs;
    registration->intervalMs = intervalMs;
    registration->timerCallback = timerCallback;
    numberOfTimerRegistrations ++;
}

void MySystem::tick(short timePassedMs) {
    // step timers
    for (int i = 0; i < numberOfTimerRegistrations; i ++) {
        TimerRegistration * registration = &timerRegistrations[i];
        if ((registration->countDownMs -= timePassedMs) < 0) {
            while ((registration->countDownMs += registration->intervalMs) < 0);
            registration->timerCallback->timerCallback();
        }
    }
}