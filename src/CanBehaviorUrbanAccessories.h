#pragma once

#include "CanBehavior.h"

class CanBehaviorUrbanAccessories : public CanBehavior {
	public:
		CanBehaviorUrbanAccessories() { }

		void transmit();

		void receive(CanMessage& msg) { }
	
	protected:
		void _randomizeMessage(CanMessage& message);
};
