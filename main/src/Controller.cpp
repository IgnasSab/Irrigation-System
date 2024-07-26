#include "Controller.h"

void Controller::waitForRelease() {
    while(this->joystick.isPressed()) {
        this->update();
    }
}

Timer::Timer() {
    for (int i = 0; i < this->time_count; i++) {
        this->time_left[i] = 0;    
        this->time_mask[i] = false;    
    }
}

void Controller::setup() {
    this->lcd.init();
    this->lcd.backlight();
    this->lcd.clear();
    this->leds.setup();
    this->joystick.setup();
    this->buttons.setup();
    this->irrigation.setup();
}

void Controller::irrigate() {
    int update_delay = this->irrigation.getIrrigationDelay();
    if (!this->water_level.isTooLow()) {
        

        this->leds.greenOn();
        this->irrigation.openValve(); 
        this->lcd.clear();
        this->lcd.setCursor(3, 0);
        this->lcd.print("STARTING PUMP");
        delay(second);
        
        this->lcd.clear();
        this->lcd.setCursor(4, 0);
        this->lcd.print("IRRIGATING");
        delay(this->irrigation.getIrrigationDelay() > 2 * second ? this->irrigation.getIrrigationDelay() - 2 * second : 0);
        
        this->irrigation.closeValve();

        this->lcd.clear();
        this->lcd.setCursor(3, 0);
        this->lcd.print("STOPPING PUMP");
        delay(second);
        this->leds.greenOff();



    } else {
        this->lcd.clear();
        this->lcd.setCursor(2, 0);
        this->lcd.print("Not enough water");
        delay(second);
        update_delay = second;
    }
    this->update(update_delay, false);
}

Controller::Controller() : lcd(0x27, 20, 4) {
    this->automatic_irrigation = false;
    this->iterations = 0;
}

void Controller::setLEDs() {
    if (this->timer.isEmpty()) {
        this->leds.yellowOff();
    } else if (iterations % 4 == 0) {
        if (this->leds.blink_state == true) {
            this->leds.yellowOn();
        } else {
            this->leds.yellowOff();
        }
        this->leds.blink_state = !this->leds.blink_state;
    } 

    if (this->water_level.isTooLow()) {
        this->leds.redOn();
    } else {
        this->leds.redOff();
    }

}

bool Controller::update(int inner_delay = global_delay, bool do_delay = true) {

    this->setLEDs();

    iterations += inner_delay / global_delay;

    if (do_delay) {
        delay(inner_delay);
    }
    if (this->timer.updateTime(inner_delay) || 
        this->moisture.lowMoisture()) {
        this->irrigate();
        return true;
    }
    return false;
}

bool Timer::isFull() {
    int count = 0;
    for (int i = 0; i < this->time_count; i++) {
        count += this->time_mask[i];
    }
    return count == this->time_count;
}

bool Timer::isEmpty() {

    for (int i = 0; i < this->time_count; i++) {
        if (this->time_mask[i] == true) {
            return false;
        }    
    }
    return true;
}

bool Timer::updateTime(int time_diff) {
    for (int i = 0; i < this->time_count; i++) {
        if (this->time_mask[i] == false) {
            continue;
        } else if (this->time_left[i] > 0) { // If timer is set
            this->time_left[i] -= time_diff;
        } else {
            this->time_left[i] = 0;
            this->time_mask[i] = false;
            return true;
        }
    }
    return false;
}



void Controller::quickIrrigation() { // TODO
    this->irrigate();
}

void sort(int time_left[], bool time_mask[], int size) {
    // Perform bubble sort
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (time_left[j] < time_left[j + 1]) {
                int temp = time_left[j];
                time_left[j] = time_left[j + 1];
                time_left[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < size; i++) {
        time_mask[i] = time_left[i] > 0; 
    }

}

void Controller::setIrrigation() { // TODO

    this->lcd.clear(); 
    if (this->timer.isFull()) {
        this->lcd.setCursor(2, 0);
        this->lcd.print("Limit is reached");
        this->update(second);
        return;
    }

    Time_state time_state = DAYS;
    int days = 0;
    int hours = 0;
    this->lcd.setCursor(2, 0);
    this->lcd.print("Fix day and hour");
    Direction joystick_direction = NEUTRAL;
    while( !buttons.isYellowPressed() ) {
        joystick_direction = joystick.getDirection();
        switch (time_state) {
            case DAYS:
                this->lcd.setCursor(6, 3);
                this->lcd.print("^^");
                this->lcd.setCursor(10, 3);
                this->lcd.print("  ");
                if ((joystick_direction == UP || joystick_direction == DOWN)
                    && joystick_direction != LEFT && joystick_direction != RIGHT) {
                    if (joystick_direction == UP) {
                        days = (days < 10 ? days + 1 : days);
                    } else {
                        days = (days > 0 ? days - 1 : days);
                    } 
                    break;
                } else if (joystick_direction == RIGHT) {
                    time_state = HOURS;
                    break;
                }
                break;
            case HOURS:
                this->lcd.setCursor(6, 3);
                this->lcd.print("  ");
                this->lcd.setCursor(10, 3);
                this->lcd.print("^^");
                if ((joystick_direction == UP || joystick_direction == DOWN)
                    && joystick_direction != LEFT && joystick_direction != RIGHT) {
                    if (joystick_direction == UP) {
                        hours = (hours < 23 ? hours+ 1 : hours);
                    } else {
                        hours = (hours> 0 ? hours - 1 : hours);
                    } 
                    break;
                } else if (joystick_direction == LEFT) {
                    time_state = DAYS;
                    break;
                }
                break;
        }

        this->lcd.setCursor(6, 2);
        this->lcd.print((days < 10 ? "0" + String(days) : String(days)) + "::" + (hours < 10 ? "0" + String(hours) : String(hours)));

        if (this->joystick.isPressed() && (days != 0 || hours != 0)) {
            this->waitForRelease();
            for (int i = 0; i < this->timer.time_count; i++) {
                if (this->timer.time_mask[i] == false) {
                    this->timer.time_left[i] = day * days + hour * hours;
                    this->timer.time_mask[i] = true; 
                    break;
                }
            }
            break;
        }
        this->update();
    }



    sort(this->timer.time_left, this->timer.time_mask, this->timer.time_count);

}   

void Controller::printCheckScreen() {
    int i = 0;
    while (i < this->timer.time_count && this->timer.time_mask[i] == true) {
        this->lcd.setCursor(1, i);
        this->lcd.print(String(i + 1) + ".");
        this->lcd.setCursor(4, i);
        this->lcd.print("Days:" + String(this->timer.time_left[i] / day) + " Hours:" + String((this->timer.time_left[i] % day) / hour));
        i++;
    }
}

void Controller::checkIrrigation() { // TODO
    int occupied = 0;
    int pointer = 0;
    for (int i = 0; i < timer.time_count; i++) {
        occupied += timer.time_mask[i];
    }
    this->lcd.clear();
    if (occupied == 0) {
        this->lcd.setCursor(5, 0);
        this->lcd.print("Empty list");
        this->update(second);
        return;
    } else {
        this->lcd.setCursor(0, 0);
        this->lcd.print("~");
    }
    Direction joystick_direction = NEUTRAL;
    printCheckScreen();
    while ( !buttons.isYellowPressed() ) {
        if ((joystick_direction == UP || joystick_direction == DOWN)
            && joystick_direction != LEFT && joystick_direction != RIGHT) {
            this->lcd.setCursor(0, pointer);
            this->lcd.print(" ");
            if (joystick_direction == UP) {
                pointer = (pointer > 0 ? pointer - 1 : pointer);
            } else {
                pointer = (pointer < occupied - 1 ? pointer + 1 : pointer);
            } 
            this->lcd.setCursor(0, pointer);
            this->lcd.print("~");
        } else if (this->joystick.isPressed()) {
            this->waitForRelease();
            occupied = (occupied > 0 ? occupied - 1 : 0);
            this->timer.time_left[pointer] = 0;
            this->timer.time_mask[pointer] = false;
            sort(this->timer.time_left, this->timer.time_mask, this->timer.time_count);

            this->lcd.clear();
            if (occupied == 0) {
                this->lcd.setCursor(5, 0);
                this->lcd.print("Empty list");
                this->update(second);
                return;
            } else {
                pointer = 0;
                this->lcd.setCursor(0, pointer);
                this->lcd.print("~");
            }
        }
 
        this->update();
        joystick_direction = this->joystick.getDirection();
        printCheckScreen();
    }

}

void Controller::automaticIrrigation() { // TODO
    this->lcd.clear();
    int automatic = this->automatic_irrigation;
    if (automatic == true) {
        this->lcd.setCursor(2, 0);
        this->lcd.print("Automatic is ON");
        this->lcd.setCursor(0, 2);
        this->lcd.print("Press to turn it OFF");
    } else {
        this->lcd.setCursor(2, 0);
        this->lcd.print("Automatic is OFF");
        this->lcd.setCursor(0, 2);
        this->lcd.print("Press to turn it ON");
    }
    while ( !buttons.isYellowPressed() ) {
        if (joystick.isPressed()) {
            this->waitForRelease();
            automatic = !automatic;
            this->lcd.clear();
            if (automatic == true) {
                this->leds.blueOn();
                this->lcd.setCursor(2, 0);
                this->lcd.print("Automatic is ON");
                this->lcd.setCursor(0, 2);
                this->lcd.print("Press to turn it OFF");
            } else {
                this->leds.blueOff();
                this->lcd.setCursor(2, 0);
                this->lcd.print("Automatic is OFF");
                this->lcd.setCursor(0, 2);
                this->lcd.print("Press to turn it ON");
            }
        }  
        if (this->update()) {
            return;
        }
    }
    this->automatic_irrigation = automatic;

}

void Controller::printStartingScreen(State& state, bool first = false)
{
    if (first) {
        this->lcd.clear();
        this->lcd.setCursor(2, 0);
        this->lcd.print("QUICK");
        this->lcd.setCursor(2, 1);
        this->lcd.print("AUTO.");
        this->lcd.setCursor(10, 0);
        this->lcd.print("SET TIME");
        this->lcd.setCursor(10, 1);
        this->lcd.print("CHECK TIME");
        this->lcd.setCursor(3, 2);
        this->lcd.print("Opening Screen");
        this->lcd.setCursor(2, 3);
        this->lcd.print("Navigate Options");
    }
    printCursors();
    switch (state.getFutureState()) {
        case State::QUICK_IRRIGATION:
            this->lcd.setCursor(0, 0);
            break;
        case State::SET_IRRIGATION:
            this->lcd.setCursor(8, 0);
            break;                                                            
        case State::CHECK_IRRIGATION:
            this->lcd.setCursor(8, 1);
            break;
        case State::AUTOMATIC_IRRIGATION:
            this->lcd.setCursor(0, 1);
            break;
    }
    this->lcd.print("~");
}

void Controller::printCursors() {
    this->lcd.setCursor(0, 0);
    this->lcd.print("}");
    this->lcd.setCursor(0, 1);
    this->lcd.print("}");
    this->lcd.setCursor(8, 0);
    this->lcd.print("}");
    this->lcd.setCursor(8, 1);
    this->lcd.print("}");
}