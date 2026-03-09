#include <Arduino.h>

#include "mqtt.h"
#include "network.h"
#include "nvs_handling.h"
#include "pins.h"
#include "sensors.h"
#include "setup_webpage.h"

// credentials of local network
String ssid;
String password;


void setup()
{
  setupPins();
  digitalWrite(LED, HIGH);
  
  Serial.begin(115200);
  
  if (!setupNVS() || digitalRead(RESET_BUTTON) == LOW)
  {
    setupWebpage("Heizungsueberwachung", "12345678");
  }
  
  ssid = getSavedSSID();
  password = getSavedPassword();
  
  reconnectWiFi(ssid.c_str(), password.c_str());
  
  setupMQTT(getWiFiClient(), getSavedClientID());

  setupSensors();
  
  digitalWrite(LED, LOW);
}

void loop()
{
  reconnectWiFi(ssid.c_str(), password.c_str());
  
  mqttLoop();
  
  char dataBuffer[10];
  snprintf(dataBuffer, sizeof(dataBuffer), "%.1f", getSensorData(0));
  mqttPublish(dataBuffer);
  
  delay(2000);
}