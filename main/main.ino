// Non-local definitions & declarations:
#include "src/State.h" 
#include "src/components.h"
#include "src/Controller.h"
#include <LiquidCrystal_I2C.h>

// Constant definitions:
#define second 1000
#define minute 60000
#define hour 3600000
#define day 86400000
////////////////////////

// LCD Screen settings:
LiquidCrystal_I2C lcd(0x27, 20, 4);
//////////////////////////////////////////

// LED settings:
#define pin_LED_RED 8
#define pin_LED_BLUE 9
#define pin_LED_GREEN 10
#define pin_LED_YELLOW 13
//////////////////////

// Joystick settings:
#define pin_JOYSTICK_X A0       
#define pin_JOYSTICK_Y A1
#define pin_JOYSTICK_BUTTON 2
///////////////////////////

// Button settings:
#define pin_BUTTON_GREEN 6
#define pin_BUTTON_YELLOW 7
/////////////////////////

// Global variables:
State state;
Joystick joystick(pin_JOYSTICK_X, pin_JOYSTICK_Y, pin_JOYSTICK_BUTTON);
Buttons buttons(pin_BUTTON_GREEN, pin_BUTTON_YELLOW);
LEDS leds(pin_LED_GREEN, pin_LED_YELLOW, pin_LED_BLUE, pin_LED_RED);
Controller controller;
////////////////////


// Function headers:
void printStartingScreen();
void printCursors();
/////////////////////////////////////////////

void setup() {

    // LCD Screen setup:
    lcd.init(); // initialize the lcd
    lcd.backlight();
    lcd.clear();

    // Serial communication setup:
    Serial.begin(9600);
    Serial.setTimeout(10);


    // Signify the start of the program: 
    Serial.println("START");

    // Setup the pins:
    leds.setup();
    
    joystick.setup();

    buttons.setup();

    // Display LCD:
    printStartingScreen(); 
}


void loop() {

    joystick.readValues();

    if (state.updateFutureState(joystick.joystick_x_val, joystick.joystick_y_val)) printStartingScreen();
    if (joystick.isPressed()) state.updateCurrentState();
    if (state.getCurrentState() != State::STARTING_SCREEN) {
        state.updateCurrentState();
        performAction();
        state.setCurrentState(State::STARTING_SCREEN);
    }

    delay(second / 5);
}

void performAction() {
    switch(state.getCurrentState()) {
        case State::QUICK_IRRIGATION:
            controller.quickIrrigation();
            break;
        case State::SET_IRRIGATION:
            controller.setIrrigation();
            break;
        case State::CHECK_IRRIGATION:
            controller.checkIrrigation();
            break;
        case State::AUTOMATIC_IRRIGATION:
            controller.automaticIrrigation();
            break;
    }
}

void printStartingScreen()
{
    printCursors();
    switch (state.getFutureState()) {
        case State::QUICK_IRRIGATION:
            lcd.setCursor(0, 0);
            break;
        case State::SET_IRRIGATION:
            lcd.setCursor(7, 0);
            break;
        case State::CHECK_IRRIGATION:
            lcd.setCursor(7, 1);
            break;
        case State::AUTOMATIC_IRRIGATION:
            lcd.setCursor(0, 1);
            break;
    }
    lcd.print("~");
    lcd.setCursor(2, 0);
    lcd.print("Quick");
    lcd.setCursor(2, 1);
    lcd.print("Automatic");
    lcd.setCursor(2, 2);
    lcd.print("Set Timer");
    lcd.setCursor(2, 3);
    lcd.print("Check timer");
}

void printCursors() {
    lcd.setCursor(0, 0);
    lcd.print("{");
    lcd.setCursor(0, 1);
    lcd.print("{");
    lcd.setCursor(0, 2);
    lcd.print("{");
    lcd.setCursor(0, 3);
    lcd.print("{");
}
