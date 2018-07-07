#include <esp8266wifi.h>
#include <esp8266httpclient.h>
#include "TimeSynchronizer.h"

TimeSynchronizer::TimeSynchronizer(MySystem * mySystem) {
    mySystem->registerTimer(1000, this);
    syncTime();
}

void TimeSynchronizer::syncTime() {
    if (refetchCountDown -- < 0) {
        if (WiFi.status() == WL_CONNECTED) {
            refetchCountDown = 5;
            HTTPClient http;
            const char * headerNames [] = {"Date"};
            http.collectHeaders(headerNames, 1);
            http.begin("http://intro.hu");
            int httpCode = http.GET();
            if (httpCode == 200) {
                String dateHeader = http.header(headerNames[1]);
                //  Fri, 06 Jul 2018 21:34:56 GMT
                int firstColonIndex = dateHeader.indexOf(':');
                
                int headerCount = http.headers();
                for (int i = 0; i < headerCount; i ++) {
                    String headerName = http.headerName(i);
                    Serial.println(headerName);
                    Serial.println(http.header(i));
                }
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