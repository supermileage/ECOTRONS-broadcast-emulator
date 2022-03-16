// Simulators
#include "SimProto.h"
#include "SimUrban.h"
#include "SimFc.h"

// Can Behaviors (for Urban only)
#include "CanBehaviorUrbanAccessories.h"
#include "CanBehaviorTinyBms.h"
#include "CanBehaviorOrionBms.h"
#include "CanBehaviorSteering.h"

// SELECT VEHICLE: PROTO URBAN FC 
#define URBAN

#ifdef PROTO
    SimProto sim(100);
#elif defined(URBAN)
    SimUrban sim(250);
#elif defined(FC)
    SimFc sim(1000);
#endif

void setup() {

    randomSeed(analogRead(A0));

    #ifdef URBAN
        sim.addBehavior(new CanBehaviorUrbanAccessories());
        sim.addBehavior(new CanBehaviorTinyBms());
        sim.addBehavior(new CanBehaviorOrionBms());
        sim.addBehavior(new CanBehaviorSteering());
    #endif

    sim.begin();

}


void loop() {

    sim.handle();

}


