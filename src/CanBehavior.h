#ifndef CAN_BEHAVIOR_H_
#define CAN_BEHAVIOR_H_

#include "SimCan.h"
#include "mcp2515_can.h"

struct CanMessage;
class SimCan;
class Sender;

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

		void setSender(Sender* sender);

	protected:
		Sender* _sender;
};

#endif