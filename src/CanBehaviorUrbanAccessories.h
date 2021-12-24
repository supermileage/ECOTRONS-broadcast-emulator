#ifndef URBAN_ACCESSORIES_BEHAVIOR_H_
#define URBAN_ACCESSORIES_BEHAVIOR_H_

#include "CanBehavior.h"

class CanBehaviorUrbanAccessories : public CanBehavior {
	public:
		CanBehaviorUrbanAccessories() { }

		void transmit();

		void receive(CanMessage& msg) { }
	
	protected:
		void _randomizeMessage(CanMessage& message);
};

#endif