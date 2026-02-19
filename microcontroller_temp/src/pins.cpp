#include "pins.h"
#include <Arduino.h>


void setupPins() {
    pinMode(LED, OUTPUT);
    pinMode(RESET_BUTTON, INPUT_PULLUP);
}