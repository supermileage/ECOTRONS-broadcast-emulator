// Simulators
#include "SimProto.h"
#include "SimUrban.h"
#include "SimFc.h"

// Can Behaviors (for Urban only)
#include "CanBehaviorUrbanAccessories.h"
#include "CanBehaviorTinyBms.h"
#include "CanBehaviorOrionBms.h"
#include "CanBehaviorSteering.h"
#include "CanBehaviorBmsSwitcher.h"

// SELECT VEHICLE: PROTO URBAN FC 
#define URBAN

#ifdef PROTO
    SimProto sim(100);
#elif defined(URBAN)
    SimUrban sim(500);

	// For testing BmsManager
	#define INTERVAL 2000
	CanBehaviorTinyBms tiny;
	CanBehaviorOrionBms orion;
	CanBehaviorBmsSwitcher switcher(&orion, &tiny);
	// CanBehaviorUrbanAccessories accessories;
#elif defined(FC)
    SimFc sim(1000);
#endif

void setup() {
    randomSeed(analogRead(A1));
    #ifdef URBAN
		sim.addBehavior(&switcher);
		// sim.addBehavior(&accessories);
    #endif

    sim.begin();
}

void loop() {
    sim.handle();
}


