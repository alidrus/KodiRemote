// vim: syntax=arduino autoindent expandtab tabstop=4 shiftwidth=4 softtabstop=4:

#define MOVEMENT_CPP
#undef DEBUG_MODE

#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "Movement.h"
#include "Secrets.h"

void sendMovement(int direction) {
    StaticJsonDocument<200> rpc;

    switch(direction) {
        case MOVEMENT_SELECT:
            rpc["method"] = "Input.Select";
            break;
        case MOVEMENT_BACK:
            rpc["method"] = "Input.Back";
            break;
        case MOVEMENT_UP:
            rpc["method"] = "Input.Up";
            break;
        case MOVEMENT_DOWN:
            rpc["method"] = "Input.Down";
            break;
        case MOVEMENT_LEFT:
            rpc["method"] = "Input.Left";
            break;
        case MOVEMENT_RIGHT:
            rpc["method"] = "Input.Right";
            break;
        default:
            return;
            break;
    }

    rpc["jsonrpc"] = "2.0";
    rpc["id"] = "1";

    String jsonPayload;
    serializeJson(rpc, jsonPayload);

    HTTPClient http;
    http.begin(JSONRPC_URL);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonPayload);

#ifdef DEBUG_MODE
	// Check the response code
	if (httpResponseCode > 0) {
		Serial.print("HTTP Response code: ");
		Serial.println(httpResponseCode);
		String response = http.getString();  // Get the response payload
		Serial.println("Response:");
		Serial.println(response);
	} else {
		Serial.print("Error code: ");
		Serial.println(httpResponseCode);
	}
#endif

    http.end();
}
