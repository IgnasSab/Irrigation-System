// Non-local definitions & declarations:
#include "src/State.h" 
#include "src/Controller.h"
///////////////////////////////////////

// Global variables:
State state;
Controller controller;
//////////////////////


// Function headers:
void performAction();
/////////////////////
    
void setup() {

    // Serial communication setup:
    Serial.begin(9600);
    Serial.setTimeout(10);

    // Setup all of the components:
    controller.setup();

    // Signify the start of the program: 
    Serial.println("START");

    // Display LCD:
    controller.printStartingScreen(state, true); 
}


void loop() {

    Direction joystick_direction = controller.joystick.getDirection();
    if (state.changeFutureState(joystick_direction)) { // Wait for a change 
        controller.printStartingScreen(state); // Move cursor in the menu
    } else if (controller.joystick.isPressed()) {
        controller.waitForRelease();
        state.updateCurrentState(); // Go to other state
    }
    if (state.getCurrentState() != State::STARTING_SCREEN) { // Check if state is different than menu
        performAction(); // Do an action corresponding to the state you are in
        state.setCurrentState(State::STARTING_SCREEN); // Go back to menu
        controller.printStartingScreen(state, true); // Print menu (starting screen)
    }
    bool irrigated = controller.update(); // Make all components up do date 
    if (irrigated == true) {
        controller.printStartingScreen(state, true); // Print menu (starting screen)
        Serial.println("HERE");
    }

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


