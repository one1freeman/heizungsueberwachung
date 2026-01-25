#ifndef NETWORK_H
#define NETWORK_H

bool startAP(const char* ssid, const char* password);
bool shutdownAP();
bool connectToWiFi(const char* ssid, const char* password);
bool reconnect(const char* ssid, const char* password);

#endif