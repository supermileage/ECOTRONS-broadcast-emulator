#ifndef CAN_BMS_BEHAVIOR_H_
#define CAN_BMS_BEHAVIOR_H_

#include "CanBehavior.h"

class CanBmsBehavior : public CanBehavior {
	public:
		CanBmsBehavior() { }

		void transmit(mcp2515_can can);

		void receive(mcp2515_can can);
	private:
		

		void _processBmsRequest();
};

#endif