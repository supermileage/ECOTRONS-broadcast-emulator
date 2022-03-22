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
    SimUrban sim(500);

	// For testing BmsManager
	#define INTERVAL 2000
	CanBehavior* tiny;
	CanBehavior* orion;
	uint64_t lastTime = 0;
	bool currentIsTiny = true;
#elif defined(FC)
    SimFc sim(1000);
#endif

void setup() {
    randomSeed(analogRead(A0));

	tiny = new CanBehaviorTinyBms();
	orion = new CanBehaviorOrionBms();

    #ifdef URBAN
        // sim.addBehavior(new CanBehaviorUrbanAccessories());
        // sim.addBehavior(new CanBehaviorTinyBms());
        sim.addBehavior(tiny);
		sim.addBehavior(orion);
        // sim.addBehavior(new CanBehaviorSteering());
    #endif

    sim.begin();
	sim.removeBehavior(orion);
}


void loop() {

    sim.handle();

	if (millis() > lastTime + INTERVAL) {
		if (currentIsTiny) {
			sim.removeBehavior(tiny);
			sim.addBehavior(orion);
			currentIsTiny = false;
		} else {
			sim.removeBehavior(orion);
			sim.addBehavior(tiny);
			currentIsTiny = true;
		}
		lastTime = millis();
	}

}


