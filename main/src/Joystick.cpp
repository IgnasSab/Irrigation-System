#include "Components.h"

Joystick::Joystick() {

}

Direction Joystick::getDirection() {
    this->readValues();
    Direction return_direction = NEUTRAL;
    if (this->left() && !this->right() && !this->up() && !this->down()) {
        return_direction = LEFT;
    } else if (!this->left() && this->right() && !this->up() && !this->down()) {
        return_direction = RIGHT;
    } else if (!this->left() && !this->right() && this->up() && !this->down()) {
        return_direction = UP;
    } else if (!this->left() && !this->right() && !this->up() && this->down()) {
        return_direction = DOWN;
    }
    return return_direction;
}

bool Joystick::left() {
    return this->joystick_x_val < 200; 
}

bool Joystick::right() {
    return this->joystick_x_val > 800; 
}

bool Joystick::up() {
    return this->joystick_y_val < 200; 
}

bool Joystick::down() {
    return this->joystick_y_val > 800; 
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