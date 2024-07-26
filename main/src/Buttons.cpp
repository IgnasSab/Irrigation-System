#include "Components.h"

Buttons::Buttons() {
}

void Buttons::setup() {
    pinMode(this->pin_BUTTON_YELLOW, INPUT_PULLUP);
}

Buttons::isYellowPressed() {
    return !digitalRead(this->pin_BUTTON_YELLOW);
}