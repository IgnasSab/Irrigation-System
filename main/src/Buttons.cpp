#include "components.h"

Buttons::Buttons(int pin_BUTTON_GREEN, int pin_BUTTON_YELLOW) {
    this->pin_BUTTON_GREEN = pin_BUTTON_GREEN;
    this->pin_BUTTON_YELLOW = pin_BUTTON_YELLOW;
}

void Buttons::setup() {
    pinMode(this->pin_BUTTON_GREEN, INPUT_PULLUP);
    pinMode(this->pin_BUTTON_YELLOW, INPUT_PULLUP);
}

Buttons::isGreenPressed() {
    return digitalRead(this->pin_BUTTON_GREEN);
}
Buttons::isYellowPressed() {
    return digitalRead(this->pin_BUTTON_YELLOW);
}