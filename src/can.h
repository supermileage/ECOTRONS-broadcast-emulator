#pragma once

#include "can_common.h"
#include "Arduino.h"

namespace can {

	#define CAN_FRAME 0x0

	// This struct contains all the components of a CAN message. dataLength must be <= 8, 
	// and the first [dataLength] positions of data[] must contain valid data
	typedef uint8_t CanBuffer[8];
	struct CanMessage {
			uint32_t id;
			uint8_t dataLength;
			CanBuffer data;
	};

	class Delegate {
		public:
        	Delegate() { }

        	~Delegate() { }

        	virtual void send(CanMessage msg, String serialMsg) = 0;
	};
}