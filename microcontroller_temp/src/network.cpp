#include <Arduino.h>
#include <WiFi.h>
#include "network.h"

const unsigned long WIFI_CONNECT_TIMEOUT_MS = 10000;

WiFiClient wifiClient;

// Start the Access Point for configuration with the given SSID and password
bool startAP(const char *ssid, const char *pass)
{

    bool result = WiFi.softAP(ssid, pass);

    if (result)
    {
        Serial.println("Access Point started successfully");
        Serial.print("SSID: ");
        Serial.println(ssid);
        Serial.print("Password: ");
        Serial.println(pass);
    }
    else
    {
        Serial.println("Failed to start Access Point");
    }

    return result;
}

// Stop the Access Point, supposed to be called after configuration has been finished
bool shutdownAP()
{
    bool result = WiFi.softAPdisconnect(true);

    if (result)
    {
        Serial.println("Access Point stopped successfully");
    }
    else
    {
        Serial.println("Failed to stop Access Point");
    }

    return result;
}

bool connectToWiFi(const char *ssid, const char *pass)
{
    Serial.print(" SSID: ");
    Serial.println(ssid);
    Serial.print(" Password: ");
    Serial.println(pass);
    Serial.println("Connecting to WiFi");

    // Begin WiFi connection
    WiFi.begin(ssid, pass);

    unsigned long startAttemptTime = millis();

    while (WiFi.status() != WL_CONNECTED && WiFi.status() != WL_CONNECT_FAILED && millis() - startAttemptTime < WIFI_CONNECT_TIMEOUT_MS)
    {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\nConnected to WiFi successfully");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        return true;
    }
    else
    {
        Serial.println("\nFailed to connect to WiFi");
        return false;
    }
}

// (Re-)connect to the WiFi network
bool reconnectWiFi(const char *ssid, const char *pass)
{
    wl_status_t status = WiFi.status();

    if (status == WL_CONNECTED)
    {
        return true; // Already connected
    }

    Serial.println("Current WiFi status: " + String(WiFi.status()));

    if (status == WL_DISCONNECTED || status == WL_CONNECTION_LOST)
    {
        Serial.println("Trying to reconnect...");
        return WiFi.reconnect(); // Attempt to reconnect
    }

    return connectToWiFi(ssid, pass); // Try to connect again

}

Client& getWiFiClient()
{
    return wifiClient;
}