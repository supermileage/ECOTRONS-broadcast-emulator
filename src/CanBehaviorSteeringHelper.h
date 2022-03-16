#ifndef _CAN_BEHAVIOR_STEERING_HELPER_H_
#define _CAN_BEHAVIOR_STEERING_HELPER_H_

#include "can_common.h"
#include "CanBehavior.h"

class CanBehaviorSteeringHelper : public CanBehavior {
	public:
		CanBehaviorSteeringHelper();

		void transmit();

		void receive(CanMessage& msg);
	private:
		unsigned long _lastReceiveTime;
		unsigned _receivedMessageCount;
};

#endif
