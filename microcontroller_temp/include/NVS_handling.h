#ifndef EEPROM_HANDLING_H
#define NVS_HANDLING_H

bool setupNVS();
void saveCredentials(String ssid, String password, String mqttClientID);
String getSavedSSID();
String getSavedPassword();
String getSavedClientID();
void closeNVS();

#endif