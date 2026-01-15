#include <Arduino.h>
#include "pins.h"
#include "network.h"
#include "setup_webpage.h"

void setup() {
  Serial.begin(115200);
  setupPins();
  // Start the Access Point
  startAP("Heizungsueberwachung", "12345678");
  if (!serverSetup()) {
    Serial.println("Failed to setup server");
  }
}

void loop() {
  serverHandleClient();
  delay(10);
}