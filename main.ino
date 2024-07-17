
// Constant definitions:
#define second_milliseconds 1000
#define minute_milliseconds 60000
#define hour_milliseconds 3600000
/////////////////////////////////

// LCD Screen settings:
#include <LiquidCrystal.h>
#define rs 12
#define en 11
#define d4 2
#define d5 3
#define d6 4
#define d7 5
LiquidCrystal lcd(rs, en, d7, d6, d5, d4);
//////////////////////////////////////////


void setup() {

    // Serial communication setup:
    Serial.begin(9600);
    Serial.setTimeout(10);

    // LCD Screen setup:
    lcd.begin(16, 2);
    lcd.clear();

    // Signify the start of the program: 
    Serial.println("START");

}


void loop() {

    


}