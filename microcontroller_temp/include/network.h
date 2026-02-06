#ifndef NETWORK_H
#define NETWORK_H

class WiFiClient;

bool startAP(const char* ssid, const char* password);
bool shutdownAP();
bool connectToWiFi(const char* ssid, const char* password);
bool reconnectWiFi(const char* ssid, const char* password);
Client& getWiFiClient();

#endif