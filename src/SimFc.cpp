#include "SimFc.h"
#include "fcp-common.h"

#define FC_BAUD_RATE        9600
#define NUM_FUEL_CELLS      17
#define NUM_HEADERS			6
#define BUFFER_SIZE			(NUM_HEADERS + NUM_FUEL_CELLS * 2)

void SimFc::begin(){ 
    Serial.begin(FC_BAUD_RATE);
}

void SimFc::handle(){
	int8_t dataBuffer[BUFFER_SIZE] = { 0 };
    if (millis() >= _lastUpdate + _updateInterval) {
		dataBuffer[0] = FC_HEADER_0;
		dataBuffer[1] = FC_HEADER_1;
		dataBuffer[2] = FC_HEADER_2;
		dataBuffer[3] = FC_HEADER_3;
		dataBuffer[4] = FC_HEADER_4;
		dataBuffer[5] = FC_HEADER_5;

        for (int i = NUM_HEADERS; i < BUFFER_SIZE; i+=2) {
			float val = (float)random(-12000, 12000) / 1000.0f;
            int16_t scaledVal = (int16_t)(val * 1000.0f);
			dataBuffer[i] = scaledVal >> 8;
			dataBuffer[i+1] = scaledVal & 0xFF;
        }
        Serial.write((char*)dataBuffer, NUM_HEADERS + NUM_FUEL_CELLS * 2);
        _lastUpdate = millis();
    }
}
