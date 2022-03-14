#ifndef _CAN_BEHAVIOR_STEERING_H_
#define _CAN_BEHAVIOR_STEERING_H_

#include "CanBehavior.h"

class CanBehaviorSteering : public CanBehavior {
	public:
		CanBehaviorSteering() { }

		void transmit();

		void receive(CanMessage& msg) { }
	
};

#endif