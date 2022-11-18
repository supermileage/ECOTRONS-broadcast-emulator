#include "SimFc.h"
#include "String.h"

#define FC_BAUD_RATE        9600
#define NUM_FUEL_CELLS      18

void SimFc::begin(){ 
    Serial.begin(FC_BAUD_RATE);
}

void SimFc::handle(){
    if(millis() >= _lastUpdate + _updateInterval) {
        String updateString = "";
        for (int i = 0; i < NUM_FUEL_CELLS; i++) {
            updateString.concat(String((float)random(-512, 511) / 256.0f, 2) + String(' '));
        }
        updateString.concat("\n");
        Serial.write(updateString.c_str());
        _lastUpdate = millis();
    }
}
