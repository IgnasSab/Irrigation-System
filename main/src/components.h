#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <Arduino.h>
#include "State.h"
#define second 1000

class Joystick {
    public:
        Joystick();
        bool isPressed();
        void setup();
        Direction getDirection();
    private:
        void readValues();
        bool left();
        bool right();
        bool up();
        bool down();
        const static int pin_JOYSTICK_X = A1;
        const static int pin_JOYSTICK_Y = A2;
        const static int pin_JOYSTICK_BUTTON = 2;
        int joystick_x_val;
        int joystick_y_val;
        int joystick_button_val;
        

};

class Buttons {
    private:
        const static int pin_BUTTON_GREEN = 6;
        const static int pin_BUTTON_YELLOW = 3;
    public:
        Buttons();
        isGreenPressed();
        isYellowPressed();
        void setup();

    
};

class LEDS {
    private:
        const static int pin_LED_RED = 8;
        const static int pin_LED_BLUE = 9;
        const static int pin_LED_GREEN = 10;
        const static int pin_LED_YELLOW = 12;
    public:
        LEDS();
        void setup();
        void greenOn();
        void greenOff();
        void yellowOn();
        void yellowOff();
        void blueOn();
        void blueOff();
        void redOn();
        void redOff();
        bool blink_state;
};

class Moisture {
    public:
        Moisture();
        void setup();
        bool lowMoisture();
    private:
        const static int pin_MOISTURE_LEVEL = A3;
        const static int threshold = 800;
};

class Irrigation {
    public:
        Irrigation();
        void setup();
        int getIrrigationDelay();
        void openValve();
        void closeValve();
    private:
        const static int pin_IRRIGATION = 7;
        const static int irrigation_delay = 5 * second;
};

class WaterLevel {
    public:
        WaterLevel();
        void setup()
        bool isTooLow();
    private:
        const static int pin_WATER_LEVEL = A0;
        const static int water_level_threshold = 900;
};

#endif
