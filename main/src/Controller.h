#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "State.h"
#include "Components.h"
#define int uint32_t

// Constant definitions:
#define second 1000
#define minute 60000
#define hour 3600000
#define day 86400000
#define global_delay 250

enum Time_state {
    DAYS, 
    HOURS
};

class Timer {
    public:    
        Timer();
        bool updateTime(int time_diff);
        static const int time_count = 4; // Hardcoded value
        int time_left[time_count];
        bool time_mask[time_count];
        bool isFull();
        bool isEmpty();

};

class Controller {
    public:
        Controller();
        bool update(int inner_delay = global_delay, bool do_delay = true);

        void quickIrrigation();
        void setIrrigation();
        void checkIrrigation();
        void automaticIrrigation();

        void printCheckScreen();
        void setup();
        void printStartingScreen(State& state, bool first = false);

        void waitForRelease();

        LiquidCrystal_I2C lcd;
        Joystick joystick;
        Buttons buttons;
        LEDS leds;
        Moisture moisture;
        Irrigation irrigation;
        WaterLevel water_level;
    private:
        void setLEDs();
        void irrigate();
        void printCursors();
        Timer timer;
        bool automatic_irrigation;
        int iterations;

};