// vim: syntax=arduino autoindent expandtab tabstop=4 shiftwidth=4 softtabstop=4:

#include <WiFi.h>

#include "Secrets.h"
#include "Movement.h"

#define DEBUG_MODE

unsigned long currentTimestamp = 0;

void wifiSetup() {
    // Disconnect from WiFi
    WiFi.disconnect(true, true);

    delay(1000);

    // Set hostname
    WiFi.setHostname(WIFI_HOSTNAME);

    // Set WiFi mode to station
    WiFi.mode(WIFI_STA);

    // WiFi credentials
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

#ifdef DEBUG_MODE
    // DEBUG messages on serial console
    Serial.print("Connecting Wifi");
#endif

    int counter = 0;
    while (WiFi.status() != WL_CONNECTED) {
        if (counter > 10) {
            return;
        }

#ifdef DEBUG_MODE
        Serial.print(".");
#endif

        delay(500);

        counter++;
    }

#ifdef DEBUG_MODE
    // DEBUG messages on serial console
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("MAC address: ");
    Serial.println(WiFi.macAddress());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("ESP32 Hostname: ");
    Serial.println(WiFi.getHostname());
    Serial.println("The IOT Server can be accessed via a browser at the following URL:");
    Serial.print("http://");
    Serial.println(WiFi.localIP());
#endif
}

int numButtonsTouched() {
    int counter = 0;

    counter += (touchingSelect ? 1 : 0);
    counter += (touchingBack ? 1 : 0);
    counter += (touchingUp ? 1 : 0);
    counter += (touchingDown ? 1 : 0);
    counter += (touchingLeft ? 1 : 0);
    counter += (touchingRight ? 1 : 0);

    return counter;
}

void updateState() {
    touchingSelect = touchRead(selectPin) < 15;
    touchingBack = touchRead(backPin) < 15;
    touchingUp = touchRead(upPin) < 15;
    touchingDown = touchRead(downPin) < 15;
    touchingLeft = touchRead(leftPin) < 15;
    touchingRight = touchRead(rightPin) < 15;

    if (numButtonsTouched() == 0 || numButtonsTouched() > 1) {
        isBusy = false;
        return;
    }

    if (isBusy) {
        return;
    }

    if (touchingSelect) {
        sendMovement(MOVEMENT_SELECT);
        isBusy = true;
    }

    if (touchingBack) {
        sendMovement(MOVEMENT_BACK);
        isBusy = true;
    }

    if (touchingUp) {
        sendMovement(MOVEMENT_UP);
        isBusy = true;
    }

    if (touchingDown) {
        sendMovement(MOVEMENT_DOWN);
        isBusy = true;
    }

    if (touchingLeft) {
        sendMovement(MOVEMENT_LEFT);
        isBusy = true;
    }

    if (touchingRight) {
        sendMovement(MOVEMENT_RIGHT);
        isBusy = true;
    }
}

void setup() {
#ifdef DEBUG_MODE
    Serial.begin(115200);
    delay(1000);
#endif

    // Setup WiFi
    wifiSetup();
}

void loop() {
    currentTimestamp = millis();

    if (currentTimestamp % 10 == 0) {
        // update the current state if there are changes
        updateState();
    
#ifdef DEBUG_MODE
        // debugging messages
        Serial.print("touchingSelect = ");
        Serial.print((touchingSelect ? "1" : "0"));
        Serial.print(", ");
        Serial.print("touchingBack = ");
        Serial.print((touchingBack ? "1" : "0"));
        Serial.print(", ");
        Serial.print("touchingUp = ");
        Serial.print((touchingUp ? "1" : "0"));
        Serial.print(", ");
        Serial.print("touchingDown = ");
        Serial.print((touchingDown ? "1" : "0"));
        Serial.print(", ");
        Serial.print("touchingLeft = ");
        Serial.print((touchingLeft ? "1" : "0"));
        Serial.print(", ");
        Serial.print("touchingRight = ");
        Serial.print((touchingRight ? "1" : "0"));
        Serial.println();
#endif
    }
}
