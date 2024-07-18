#include "components.h"

LEDS::LEDS(int pin_LED_GREEN, int pin_LED_YELLOW, int pin_LED_BLUE, int pin_LED_RED) {
    this->pin_LED_GREEN = pin_LED_GREEN;
    this->pin_LED_YELLOW = pin_LED_YELLOW;
    this->pin_LED_BLUE = pin_LED_BLUE;
    this->pin_LED_RED = pin_LED_RED;
}

void LEDS::setup() {
    pinMode(this->pin_LED_RED, OUTPUT);
    pinMode(this->pin_LED_BLUE, OUTPUT);
    pinMode(this->pin_LED_GREEN, OUTPUT);
    pinMode(this->pin_LED_YELLOW, OUTPUT);
}

void LEDS::greenOn() {
    digitalWrite(this->pin_LED_GREEN, HIGH);
}
void LEDS::greenOff() {
    digitalWrite(this->pin_LED_GREEN, LOW);
}

void LEDS::yellowOn() {
    digitalWrite(this->pin_LED_YELLOW, HIGH);
}
void LEDS::yellowOff() {
    digitalWrite(this->pin_LED_YELLOW, LOW);
}

void LEDS::blueOn() {
    digitalWrite(this->pin_LED_BLUE, HIGH);
}
void LEDS::blueOff() {
    digitalWrite(this->pin_LED_BLUE, LOW);
}

void LEDS::redOn() {
    digitalWrite(this->pin_LED_RED, HIGH);
}
void LEDS::redOff() {
    digitalWrite(this->pin_LED_RED, LOW);
}
