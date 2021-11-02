#include "Sim.h"
#include "SimEcu.h"
#include "SimCan.h"

SimEcu ecu;
SimCan can;

Sim *simulators[] = {&ecu, &can};

void setup() {

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


