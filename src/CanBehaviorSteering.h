#pragma once

#include "CanBehavior.h"

class CanBehaviorSteering : public CanBehavior {
	public:
		CanBehaviorSteering() { }

		void transmit();

		void receive(CanMessage& msg) { }
		
};