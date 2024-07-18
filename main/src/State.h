#ifndef STATE_H
#define STATE_H

// Enum definitions:
enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};


// Class definitions:
class State {
    public: 
        enum State_enum {
            STARTING_SCREEN,
            QUICK_IRRIGATION,
            SET_IRRIGATION,
            CHECK_IRRIGATION,
            AUTOMATIC_IRRIGATION
        };
        State();
        State_enum getCurrentState();
        State_enum getFutureState();
        void setFutureState(State_enum current_state);
        void setCurrentState(State_enum future_state);
        bool changeFutureState(Direction direction);
        void updateCurrentState();
        bool updateFutureState(int joystick_x_val, int joystick_y_val);
        ~State();
    private:
        State_enum current_state;
        State_enum future_state;

};
///////////////////////////////////

#endif
