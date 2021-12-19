#ifndef URBAN_ACCESSORIES_BEHAVIOR_H_
#define URBAN_ACCESSORIES_BEHAVIOR_H_

#include "CanBehavior.h"

const CanMessage TEST1 = {0x14, 8, {0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
const CanMessage TEST2 = {0x2D, 8, {0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00}};
const CanMessage TRANSMIT_MSGS[] = {TEST1, TEST2};

class UrbanAccessoriesBehavior : public CanBehavior {
	public:
		UrbanAccessoriesBehavior() { }

		void transmit(mcp2515_can can);

		void receive(mcp2515_can can) { }
	
	protected:
		void _randomizeMessages();
};

#endif