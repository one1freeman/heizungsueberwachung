#include <Arduino.h>
#include "pins.h"
#include "network.h"
#include "NVS_handling.h"
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

  reconnect(ssid.c_str(), password.c_str());
}

void loop()
{
  reconnect(ssid.c_str(), password.c_str());
  delay(2000);
}