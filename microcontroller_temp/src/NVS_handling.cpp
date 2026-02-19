#include <Arduino.h>
#include <Preferences.h>
#include "nvs_handling.h"

#define SSID_KEY "ssid"
#define PASSWORD_KEY "password"
#define CLIENTID_KEY "mqttID"

Preferences preferences;

bool setupNVS() {
    if (!preferences.begin("creds", false)) {
        Serial.println("Failed to initialize NVS");
    } else {
        Serial.println("NVS initialized successfully");
        return true;
    }

    if (preferences.getBool("configured")) {
        Serial.println("Device already configured.");
        return true;
    }

    Serial.println("Device not configured yet.");
    return false;
}


/*
 * Saves credentials to NVS only if they have changed, to minimize write cycles.
 * Also sets a "configured" flag to true after saving.
 */

void saveCredentials(String ssid, String password, String mqttClientID) {
    if (preferences.getString(SSID_KEY) != ssid) {
        preferences.putString(SSID_KEY, ssid);
        Serial.println("SSID saved to NVS");
    } else {
        Serial.println("SSID unchanged, not saving to NVS");
    }
    
    if (preferences.getString(PASSWORD_KEY) != password) {
        preferences.putString(PASSWORD_KEY, password);
        Serial.println("Password saved to NVS");
    } else {
        Serial.println("Password unchanged, not saving to NVS");
    }
    
    if (preferences.getString(CLIENTID_KEY) != mqttClientID) {
        preferences.putString(CLIENTID_KEY, mqttClientID);
        Serial.println("MQTT Client ID saved to NVS");
    } else {
        Serial.println("MQTT ID unchanged, not saving to NVS");
    }
    
    preferences.putBool("configured", true);
}

String getSavedSSID() {
    return preferences.getString("ssid", "");
}

String getSavedPassword() {
    return preferences.getString("password", "");
}

String getSavedClientID() {
    return preferences.getString("mqttID", "Client0");
}

void closeNVS() {
    preferences.end();
}