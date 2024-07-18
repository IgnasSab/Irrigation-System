#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "State.h"
#include "components.h"

// Constant definitions:
#define second 1000
#define minute 60000
#define hour 3600000
#define day 86400000

enum Time_state {
    DAYS, 
    HOURS
};


class Timer {
    public:    
        Timer();
        void updateTime(int time_diff);
        static const int timer_count = 4; // Hardcoded value
        int time_left[timer_count];
        bool timer_mask[timer_count];

};


class Controller {
    public:
        Controller(int pin_JOYSTICK_X, int pin_JOYSTICK_Y, int pin_JOYSTICK_BUTTON,
    int pin_LED_GREEN, int pin_LED_YELLOW, int pin_LED_BLUE, int pin_LED_RED,
    int pin_BUTTON_GREEN, int pin_BUTTON_YELLOW);
        void update(int delay);
        void quickIrrigation();
        void setIrrigation();
        void checkIrrigation();
        void automaticIrrigation();
        void printStartingScreen(State& state);
        LiquidCrystal_I2C lcd;
        Joystick joystick;
        Buttons buttons;
        LEDS leds;
    private:
        void printCursors();
        Timer timer;
        bool automatic_irrigation;
};