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
#define FC

#ifdef PROTO
    SimProto sim(100);
#elif defined(URBAN)
    SimUrban sim(500);

	// For testing BmsManager
	#define INTERVAL 2000
	CanBehaviorTinyBms tiny;
	CanBehaviorOrionBms orion;
	CanBehaviorSteering steering;
	CanBehaviorUrbanAccessories accessories;
#elif defined(FC)
    SimFc sim(1000);
#endif

void setup() {
    randomSeed(analogRead(A1));
    #ifdef URBAN
		sim.addBehavior(&orion);
		sim.addBehavior(&steering);
		sim.addBehavior(&accessories);
    #endif

    sim.begin();
}

void loop() {
    sim.handle();
}


