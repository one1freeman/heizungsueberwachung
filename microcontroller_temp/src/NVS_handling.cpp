#include <Arduino.h>
#include "NVS_handling.h"
#include <Preferences.h>

Preferences preferences;

bool setupNVS() {
    if (!preferences.begin("creds", false)) {
        Serial.println("Failed to initialize NVS");
    } else {
        Serial.println("NVS initialized successfully");
    }

    if (preferences.getBool("configured")) {
        Serial.println("Device already configured.");
        return true;
    }

    Serial.println("Device not configured yet.");
    return false;
}

void saveCredentials(const char* ssid, const char* password) {
   if (preferences.getString("ssid") != String(ssid)) {
        preferences.putString("ssid", ssid);
        Serial.println("SSID saved to NVS");
    } else {
        Serial.println("SSID unchanged, not saving to NVS");
    }

    if (preferences.getString("password") != String(password)) {
        preferences.putString("password", password);
        Serial.println("Password saved to NVS");
    } else {
        Serial.println("Password unchanged, not saving to NVS");
    }

    preferences.putBool("configured", true);
}

String getSavedSSID() {
    return preferences.getString("ssid", "");
}

String getSavedPassword() {
    return preferences.getString("password", "");
}

void closeNVS() {
    preferences.end();
}