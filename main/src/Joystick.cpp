#include "components.h"

Joystick::Joystick(int pin_JOYSTICK_X, int pin_JOYSTICK_Y, int pin_JOYSTICK_BUTTON) {
    this->pin_JOYSTICK_X = pin_JOYSTICK_X;
    this->pin_JOYSTICK_Y = pin_JOYSTICK_Y;
    this->pin_JOYSTICK_BUTTON = pin_JOYSTICK_BUTTON;
}

void Joystick::readValues() {
    this->joystick_x_val = analogRead(this->pin_JOYSTICK_X);
    this->joystick_y_val = analogRead(this->pin_JOYSTICK_Y);  
}

bool Joystick::isPressed() {
    return !digitalRead(pin_JOYSTICK_BUTTON);
}

void Joystick::setup() {
    pinMode(pin_JOYSTICK_X, INPUT);
    pinMode(pin_JOYSTICK_Y, INPUT);
    pinMode(pin_JOYSTICK_BUTTON, INPUT_PULLUP);
}