#ifndef CAN_BEHAVIOR_H_
#define CAN_BEHAVIOR_H_

#include "can.h"
#include "mcp2515_can.h"

using namespace can;

/**
 * @brief Defines the set of messages to transmit and how to handle received messages
 * 
 */
class CanBehavior {
	public:
		CanBehavior() { }

		~CanBehavior() { }

		virtual void transmit() = 0;

		virtual void receive(CanMessage& msg) = 0;

		void setSender(Delegate* sender);

	protected:
		Delegate* _sender;
};

#endif