#include "Sim.h"
#include "SimEcu.h"
#include "SimCan.h"
#include "CanBmsBehavior.h"
#include "CanUrbanAccessoriesBehavior.h"

#define CAN_DEBUG 1

#if CAN_DEBUG
    CanBmsBehavior bmsBehavior;
    CanUrbanAccessoriesBehavior urbanBehavior;
    SimCan canBms(&Serial, bmsBehavior);
    SimCan canUrban(&Serial, urbanBehavior);
    Sim *simulators[] = {&canBms, &canUrban};
#else
    SimEcu ecu(&Serial);
    SimCan can;
    Sim *simulators[] = {&ecu, &can};
#endif

void setup() {
    if(CAN_DEBUG){
        Serial.begin(CAN_DEBUG_BAUD_RATE);
    }else{
        // 115200 baud rate, 8 data bits, no parity, 1 stop bit per datasheet
        Serial.begin(ECU_BAUD_RATE, SERIAL_8N1);
    }

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


