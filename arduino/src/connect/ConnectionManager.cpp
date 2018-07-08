#include "ConnectionManager.h"
#include <ESP8266WiFi.h>
#include "TimeSynchronizer.h"

ConnectionManager::ConnectionManager(MySystem * mySystem) {
    mySystem->registerTimer(500, this);
    new TimeSynchronizer(mySystem);
}

void ConnectionManager::timerCallback() {
    regularCheck();
}

void ConnectionManager::init() {
    reconnectWifi();
}

void ConnectionManager::reconnectWifi() {
    WiFi.begin("Sunshine", "Alma12345");
    waitCounter = 0;
    Serial.println("Connecting to WiFi");
}

void ConnectionManager::regularCheck() {
    if (WiFi.status() != WL_CONNECTED) {
        if (waitCounter ++ > 10) {
            WiFi.disconnect();
            reconnectWifi();
        }
    }
}