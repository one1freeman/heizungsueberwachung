#include <Arduino.h>
#include "pins.h"
#include "network.h"
#include "setup_webpage.h"

bool configurationMode = true;

void setup() {
  Serial.begin(115200);
  setupPins();
  configurationServer("Heizungsueberwachung", "12345678");
}

void loop() {
  delay(10);
}