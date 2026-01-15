#include "network.h"
#include <Arduino.h>
#include <WiFi.h>

bool startAP(const char* ssid, const char* password) {
    // Set WiFi mode to Access Point
    WiFi.mode(WIFI_AP);
    
    // Start the Access Point with the given SSID and password
    bool result = WiFi.softAP(ssid, password);
    
    if (result) {
        Serial.println("Access Point started successfully");
        Serial.print("SSID: ");
        Serial.println(ssid);
        Serial.print("Password: ");
        Serial.println(password);
    } else {
        Serial.println("Failed to start Access Point");
    }

    return result;
}

bool shutdownAP() {
    // Disconnect the Access Point
    bool result = WiFi.softAPdisconnect(true);
    
    if (result) {
        Serial.println("Access Point stopped successfully");
    } else {
        Serial.println("Failed to stop Access Point");
    }

    return result;
}

bool connectToWiFi(const char* ssid, const char* password) {
    // Set WiFi mode to Station
    WiFi.mode(WIFI_STA);
    
    // Begin WiFi connection
    WiFi.begin(ssid, password);
    
    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED && WiFi.status() != WL_CONNECT_FAILED) {
        delay(500);
        Serial.print(".");
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected to WiFi successfully");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        return true;
    } else {
        Serial.println("\nFailed to connect to WiFi");
        return false;
    }
}

// (Re-)connect to the WiFi network
bool reconnect(const char* ssid, const char* password) {
    wl_status_t status = WiFi.status();

    Serial.println("Current WiFi status: " + String(WiFi.status()));

    if (status == WL_CONNECTED)
    {
        return true; // Already connected
    } else if (status == WL_DISCONNECTED || status == WL_CONNECTION_LOST)
    {
        return WiFi.reconnect(); // Attempt to reconnect
    } else
    {
        return connectToWiFi(ssid, password); // Try to connect again
    }
}