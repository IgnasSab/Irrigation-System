#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <Arduino.h>

struct Joystick {
    int joystick_x_val;
    int joystick_y_val;
    int joystick_button_val;
    int pin_JOYSTICK_X;
    int pin_JOYSTICK_Y;
    int pin_JOYSTICK_BUTTON;
    Joystick(int pin_JOYSTICK_X, int pin_JOYSTICK_Y, int pin_JOYSTICK_BUTTON);
    void readValues();
    bool isPressed();
    void setup();
};

class Buttons {
    private:
        int pin_BUTTON_GREEN;
        int pin_BUTTON_YELLOW;
    public:
        Buttons(int pin_BUTTON_GREEN, int pin_BUTTON_YELLOW);
        isGreenPressed();
        isYellowPressed();
        void setup();

    
};

class LEDS {
    private:
        int pin_LED_RED;
        int pin_LED_BLUE;
        int pin_LED_GREEN;
        int pin_LED_YELLOW;
    public:
        LEDS(int pin_LED_GREEN, int pin_LED_YELLOW, int pin_LED_BLUE, int pin_LED_RED);
        void setup();
        void greenOn();
        void greenOff();
        void yellowOn();
        void yellowOff();
        void blueOn();
        void blueOff();
        void redOn();
        void redOff();
};

#endif
