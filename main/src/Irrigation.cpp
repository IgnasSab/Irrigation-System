#include "Components.h"

Irrigation::Irrigation() {

}

void Irrigation::setup() {
    pinMode(this->pin_IRRIGATION, OUTPUT);
    this->closeValve();
}

void Irrigation::openValve() {
    digitalWrite(this->pin_IRRIGATION, LOW  );
}

void Irrigation::closeValve() {
    
    digitalWrite(this->pin_IRRIGATION, HIGH);
}

Irrigation::getIrrigationDelay() {
    return this->irrigation_delay;
}