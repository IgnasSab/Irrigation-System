// Non-local definitions & declarations:
#include "src/State.h" 
#include "src/Controller.h"


////////////////////////

// controller.LCD Screen settings:
// Constant definitions:
#define second 1000
#define minute 60000
#define hour 3600000
#define day 86400000
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
Controller controller(pin_JOYSTICK_X, pin_JOYSTICK_Y, pin_JOYSTICK_BUTTON,
    pin_LED_GREEN, pin_LED_YELLOW, pin_LED_BLUE, pin_LED_RED,
    pin_BUTTON_GREEN, pin_BUTTON_YELLOW);
////////////////////


// Function headers:

/////////////////////////////////////////////

void setup() {

    // controller.LCD Screen setup:
    controller.lcd.init(); // initialize the controller.lcd
    controller.lcd.backlight();
    controller.lcd.clear();

    // Serial communication setup:
    Serial.begin(9600);
    Serial.setTimeout(10);


    // Signify the start of the program: 
    Serial.println("START");

    // Setup the pins:
    controller.leds.setup();
    controller.joystick.setup();
    controller.buttons.setup();

    // Display LCD:
    controller.printStartingScreen(state); 
}


void loop() {

    controller.joystick.readValues();

    if (state.updateFutureState(controller.joystick.joystick_x_val, controller.joystick.joystick_y_val)) controller.printStartingScreen(state);
    if (controller.joystick.isPressed()) {
        state.updateCurrentState();
    }
    if (state.getCurrentState() != State::STARTING_SCREEN) {
        performAction();
        state.setCurrentState(State::STARTING_SCREEN);
        controller.printStartingScreen(state);
    }

    delay(second);
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


