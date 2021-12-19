#ifndef CAN_BEHAVIOR_H_
#define CAN_BEHAVIOR_H_

#include "SimCan.h"
#include "mcp2515_can.h"

class CanBehavior {
	public:
		CanBehavior() { }

		~CanBehavior() { }

		virtual void transmit(mcp2515_can can) = 0;

		virtual void receive(mcp2515_can can) = 0;

		void setSerial(Serial* serial) : _serial(serial) { }
		
	protected:
		Serial _serial = NULL;
};

#endif