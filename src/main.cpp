#include "Sim.h"
#include "SimEcu.h"
#include "SimCan.h"

#include "CanBmsBehavior.h"
#include "CanBehaviorUrbanAccessories.h"

// Select between: MODE_CAN MODE_ECU
#define MODE_CAN 
// #define MODE_ECU

#ifdef MODE_CAN
    CanBmsBehavior bmsBehavior;
    CanBehaviorUrbanAccessories urbanBehavior;
    CanBehavior* behaviors[] = { &bmsBehavior, &urbanBehavior, NULL };
    SimCan simCan(behaviors);
    Sim *simulators[] = { &simCan };
#elif defined(MODE_ECU)
    SimEcu ecu(&Serial);
    Sim *simulators[] = {&ecu};
#endif

void setup() {
    #ifdef MODE_CAN
        Serial.begin(CAN_DEBUG_BAUD_RATE);
    #elif defined(MODE_ECU)
        // 115200 baud rate, 8 data bits, no parity, 1 stop bit per datasheet
        Serial.begin(ECU_BAUD_RATE, SERIAL_8N1);
    #endif

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


