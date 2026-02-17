#include <Arduino.h>

#include "mqtt.h"
#include "network.h"
#include "NVS_handling.h"
#include "pins.h"
#include "sensors.h"
#include "setup_webpage.h"

// credentials of local network
String ssid;
String password;

void setup()
{
  Serial.begin(115200);
  setupPins();

  
  if (!setupNVS())
  {
    setupWebpage("Heizungsueberwachung", "12345678");
  }

  ssid = getSavedSSID();
  password = getSavedPassword();

  reconnectWiFi(ssid.c_str(), password.c_str());

  setupMQTT(getWiFiClient(), "Client0");
}

void loop()
{
  reconnectWiFi(ssid.c_str(), password.c_str());

  mqttLoop();
  
  char buffer[5];
  snprintf(buffer, sizeof(buffer), "%.1f", getSensorData(0));
  mqttPublish(buffer);
  
  delay(2000);
}