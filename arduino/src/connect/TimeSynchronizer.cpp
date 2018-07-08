#include <esp8266wifi.h>
#include <esp8266httpclient.h>
#include "TimeSynchronizer.h"

TimeSynchronizer::TimeSynchronizer(MySystem * mySystem) {
    mySystem->registerTimer(1000, this);
    syncTime();
    this->mySystem = mySystem;
}

void TimeSynchronizer::syncTime() {
    if (refetchCountDown -- < 0) {
        if (WiFi.status() == WL_CONNECTED) {
            refetchCountDown = 60;
            HTTPClient http;
            http.begin("http://switchery-203316.appspot.com/time.text.bud");
            int httpCode = http.GET();
            if (httpCode == 200) {
                String time = http.getString();
                Serial.println(time);
                mySystem->timeString = new String(time);
            } else {
                Serial.print("Time fetch http responded:");
                Serial.println(httpCode);
            }
        }
    }
}

void TimeSynchronizer::timerCallback() {
    syncTime();
}