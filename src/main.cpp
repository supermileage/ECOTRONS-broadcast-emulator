#include "Sim.h"
#include "SimEcu.h"
#include "SimCan.h"

#define BUILTIN_LED 17

SimEcu ecu(Serial);
SimCan can(BUILTIN_LED);

Sim *simulators[] = {&ecu, &can};

void setup() {
    // 115200 baud rate, 8 data bits, no parity, 1 stop bit per datasheet
    Serial.begin(ECU_BAUD_RATE, SERIAL_8N1);

    // Start all simulators
    for(Sim *s : simulators){
        s->begin();
    }

}


void loop() {

    // Run all simulators
    for(Sim *s : simulators){
        s->handle();
    }

}


