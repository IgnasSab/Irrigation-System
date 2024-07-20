#include "Components.h"

Moisture::Moisture() {
}

void Moisture::setup() {
    pinMode(this->pin_MOISTURE_LEVEL, INPUT);
}

bool Moisture::lowMoisture() {
    return false;
    // return analogRead(this->pin_MOISTURE_LEVEL) > this->threshold;
} 