#ifndef URBAN_ACCESSORIES_BEHAVIOR_H_
#define URBAN_ACCESSORIES_BEHAVIOR_H_

#include "CanBehavior.h"

class CanUrbanAccessoriesBehavior : public CanBehavior {
	public:
		CanUrbanAccessoriesBehavior() { }

		void transmit(mcp2515_can can);

		void receive(mcp2515_can can) { }
	
	protected:
		void _randomizeMessages();
};

#endif