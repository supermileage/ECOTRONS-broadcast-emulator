#include "SimFc.h"
#include "String.h"

#define FC_BAUD_RATE        9600
#define NUM_FUEL_CELLS      18
#define NUM_HEADERS			6

#define FC_HEADER_0 0x7
#define FC_HEADER_1 0xD
#define FC_HEADER_2 0x11
#define FC_HEADER_3 0x17
#define FC_HEADER_4 0x1D
#define FC_HEADER_5 0x1F

void SimFc::begin(){ 
    Serial.begin(FC_BAUD_RATE);
}

void SimFc::handle(){
	int8_t dataBuffer[NUM_HEADERS + NUM_FUEL_CELLS] = { 0 };
    if (millis() >= _lastUpdate + _updateInterval) {
		dataBuffer[0] = FC_HEADER_0;
		dataBuffer[1] = FC_HEADER_1;
		dataBuffer[2] = FC_HEADER_2;
		dataBuffer[3] = FC_HEADER_3;
		dataBuffer[4] = FC_HEADER_4;
		dataBuffer[5] = FC_HEADER_5;

        for (int i = NUM_HEADERS; i < NUM_FUEL_CELLS; i++) {
            dataBuffer[i] = (int8_t)random(-128, 127);
        }
        Serial.write((char*)dataBuffer);
        _lastUpdate = millis();
    }
}
