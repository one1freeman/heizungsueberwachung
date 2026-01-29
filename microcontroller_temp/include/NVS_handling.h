#ifndef EEPROM_HANDLING_H
#define NVS_HANDLING_H

bool setupNVS();
void saveCredentials(const char* ssid, const char* password);
String getSavedSSID();
String getSavedPassword();
void closeNVS();

#endif