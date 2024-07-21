#include "Components.h"

WaterLevel::WaterLevel() {
    
}

void WaterLevel::setup() {
    pinMode(this->pin_WATER_LEVEL, INPUT);
}

bool WaterLevel::isTooLow() {
    return analogRead(this->pin_WATER_LEVEL) < this->water_level_threshold; // TODO
}
