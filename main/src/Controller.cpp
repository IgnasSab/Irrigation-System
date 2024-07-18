#include "Controller.h"

Timer::Timer() {
    for (int i = 0; i < this->timer_count; i++) {
        this->time_left[i] = 0;    
        this->timer_mask[i] = false;    
    }
}


Controller::Controller(int pin_JOYSTICK_X, int pin_JOYSTICK_Y, int pin_JOYSTICK_BUTTON, 
    int pin_LED_GREEN, int pin_LED_YELLOW, int pin_LED_BLUE, int pin_LED_RED, int pin_BUTTON_GREEN, int pin_BUTTON_YELLOW) 
    : lcd(0x27, 20, 4),
      joystick(pin_JOYSTICK_X, pin_JOYSTICK_Y, pin_JOYSTICK_BUTTON), 
      buttons(pin_BUTTON_GREEN, pin_BUTTON_YELLOW), 
      leds(pin_LED_GREEN, pin_LED_YELLOW, pin_LED_BLUE, pin_LED_RED) {
    
    this->automatic_irrigation = false;
}

void Controller::update(int delay) {
    this->timer.updateTime(delay);

}

void Timer::updateTime(int time_diff) {
    for (int i = 0; i < this->timer_count; i++) {
        if (timer_mask[i] == false) {
            continue;
        } else if (time_left[i] > 0) { // If timer is set
            time_left[i] -= time_diff;
        } else {
            time_left[i] = 0;
            timer_mask[i] = false;
            Serial.println("Irrigating...");
        }
    }
}


void Controller::quickIrrigation() { // TODO
    this->lcd.clear();
    this->lcd.setCursor(3, 0);
    this->lcd.print("OPENING VALVES");
    delay(3 * second);
    this->lcd.setCursor(3, 0);
    this->lcd.print("CLOSING VALVES");
    delay(3 * second);
}

void Controller::setIrrigation() { // TODO
    Time_state time_state = DAYS;
    int days = 0;
    int hours = 0;
    lcd.clear(); 
    lcd.setCursor(2, 0);
    lcd.print("Fix day and hour");
    while( true ) {
        switch (time_state) {
            case DAYS:
                lcd.setCursor(6, 3);
                lcd.print("^^");
                lcd.setCursor(10, 3);
                lcd.print("  ");
                if (this->joystick.joystick_y_val < 420 || this->joystick.joystick_y_val > 580) {
                    if (this->joystick.joystick_y_val < 420) {
                        days = (days < 10 ? days + 1 : days);
                    } else if (this->joystick.joystick_y_val > 520) {
                        days = (days > 0 ? days - 1 : days);
                    } 
                    break;
                } else if (this->joystick.joystick_x_val > 580) {
                    time_state = HOURS;
                    break;
                }
                break;
            case HOURS:
                lcd.setCursor(6, 3);
                lcd.print("  ");
                lcd.setCursor(10, 3);
                lcd.print("^^");
                if (this->joystick.joystick_y_val < 420 || this->joystick.joystick_y_val > 580) {
                    if (this->joystick.joystick_y_val < 420) {
                        hours = (hours < 23 ? hours+ 1 : hours);
                    } else if (this->joystick.joystick_y_val > 520) {
                        hours= (hours> 0 ? hours - 1 : hours);
                    } 
                    break;
                } else if (this->joystick.joystick_x_val < 420) {
                    time_state = DAYS;
                    break;
                }
                break;
        }

        lcd.setCursor(6, 2);
        lcd.print((days < 10 ? "0" + String(days) : String(days)) + "::" + (hours < 10 ? "0" + String(hours) : String(hours)));

        delay(second);
        if (joystick.isPressed()) break;
        joystick.readValues();
    }
    
    for (int i = 0; i < this->timer.timer_count; i++) {
        if (timer.timer_mask[i] == false) {
            timer.time_left[i] = day * days + hour * hours; 
        }
    }

}   

void Controller::checkIrrigation() { // TODO

}

void Controller::automaticIrrigation() { // TODO
    this->automatic_irrigation = !this->automatic_irrigation;
}

void Controller::printStartingScreen(State& state)
{
    this->lcd.clear();
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