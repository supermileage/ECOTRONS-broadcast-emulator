#ifndef CAN_BMS_BEHAVIOR_H_
#define CAN_BMS_BEHAVIOR_H_

#include "CanBehavior.h"

class CanBehaviorBms : public CanBehavior {
	public:
		CanBehaviorBms() { }

		void transmit() { }

		void receive(CanMessage& msg);

	private:
		void _processBmsRequest(CanMessage& msg);
};

#endif