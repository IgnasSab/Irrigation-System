#include "Components.h"

Buttons::Buttons() {
}

void Buttons::setup() {
    pinMode(this->pin_BUTTON_GREEN, INPUT_PULLUP);
    pinMode(this->pin_BUTTON_YELLOW, INPUT_PULLUP);
}

Buttons::isGreenPressed() {
    return digitalRead(this->pin_BUTTON_GREEN);
}
Buttons::isYellowPressed() {
    return !digitalRead(this->pin_BUTTON_YELLOW);
}