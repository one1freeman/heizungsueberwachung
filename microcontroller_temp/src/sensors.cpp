#include "sensors.h"
#include "pins.h"
#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setupSensors() {
    sensors.begin();
}

float getSensorData(int id) {
    sensors.requestTemperatures();
    return sensors.getTempCByIndex(id);
}