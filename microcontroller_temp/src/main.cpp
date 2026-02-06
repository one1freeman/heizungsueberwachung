#include <Arduino.h>

#include "mqtt.h"
#include "network.h"
#include "NVS_handling.h"
#include "pins.h"
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

  setupMQTT(getWiFiClient());
}

void loop()
{
  reconnectWiFi(ssid.c_str(), password.c_str());
  mqttPublish("test/test", "online");
  mqttLoop();
  delay(2000);
}