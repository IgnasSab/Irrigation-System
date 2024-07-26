#include "State.h"

using namespace std;

State::State() {
    this->current_state = STARTING_SCREEN;
    this->future_state = QUICK_IRRIGATION;
}

State::State_enum State::getCurrentState() {
    return this->current_state;
}
State::State_enum State::getFutureState() {
    return this->future_state;
    
}

void State::setCurrentState(State_enum current_state) {
    this->current_state = current_state; 
}
void State::setFutureState(State_enum future_state) {
    this->future_state = future_state; 
}

bool State::changeFutureState(Direction direction) {
    int changed = false;
    switch (this->future_state) {
        case QUICK_IRRIGATION:
            switch(direction) {
                case UP:
                    break;
                case DOWN:
                    this->future_state = AUTOMATIC_IRRIGATION;
                    changed = true;
                    break;
                case LEFT:
                    break;
                case RIGHT:
                    this->future_state = SET_IRRIGATION;
                    changed = true;
                    break;
                case NEUTRAL:
                    // DO NOTHING
                    break;
            }
            break;
        case SET_IRRIGATION:
            switch(direction) {
                case UP:
                    break;
                case DOWN:
                    this->future_state = CHECK_IRRIGATION;
                    changed = true;
                    break;
                case LEFT:
                    this->future_state = QUICK_IRRIGATION;
                    changed = true;
                    break;
                case RIGHT:
                    break;
                case NEUTRAL:
                    // DO NOTHING
                    break;

            }
            break;
        case CHECK_IRRIGATION:
            switch(direction) {
                case UP:
                    this->future_state = SET_IRRIGATION;
                    changed = true;
                    break;
                case DOWN:
                    break;
                case LEFT:
                    this->future_state = AUTOMATIC_IRRIGATION;
                    changed = true;
                    break;
                case RIGHT:
                    break;
                case NEUTRAL:
                    // DO NOTHING
                    break;

            }
            break;
        case AUTOMATIC_IRRIGATION:
            switch(direction) {
                case UP:
                    this->future_state = QUICK_IRRIGATION;
                    changed = true;
                    break;
                case DOWN:
                    break;
                case LEFT:
                    break;
                case RIGHT:
                    this->future_state = CHECK_IRRIGATION;
                    changed = true;
                    break;
                case NEUTRAL:
                    // DO NOTHING
                    break;

            }
            break;
    }
    return changed;
}


void State::updateCurrentState() {
    this->current_state = this->future_state;
}

State::~State() {}