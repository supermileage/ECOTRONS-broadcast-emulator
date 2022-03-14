#include "SimFc.h"

#define FC_BAUD_RATE        9600
#define FC_INTERVAL         1000
#define FC_STOP_CHARACTER   '*'

void SimFc::begin(){ 
    Serial.begin(FC_BAUD_RATE);
}

void SimFc::handle(){
    if(millis() >= _lastUpdate + FC_INTERVAL) {
        Serial.println("This is a message from the FC emulator");
        Serial.print("The emulator has been online for ");
        Serial.print(millis() / 1000);
        Serial.println("s");
        Serial.print("*");
        _lastUpdate = millis();
    }
}
