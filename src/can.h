#ifndef _CAN_NAMESPACE_H_
#define _CAN_NAMESPACE_H_

#include "Arduino.h"

namespace can {
	// Turn on/off serial debugging
	#define DEBUG_SERIAL 1

	// CAN Settings
	#define CAN_DEBUG_BAUD_RATE 115200
	#define CAN_CS_PIN          A5
	#define CAN_FRAME           0

	// Transmit Settings
	#define CAN_TRANSMIT_INTERVAL 500

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
        	Delegate()  { }

        	~Delegate() { }

        	virtual void send(CanMessage msg, String serialMsg) = 0;
	};
}

#endif