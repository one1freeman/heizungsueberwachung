#ifndef NETWORK_H
#define NETWORK_H

bool startAP(const char* ssid, const char* password);
bool shutdownAP();
bool reconnectToWiFi(const char* ssid, const char* password);

#endif