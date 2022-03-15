#pragma once

#include "CanBehavior.h"

class CanBehaviorTinyBms : public CanBehavior {
	public:
		CanBehaviorTinyBms() { }

		void transmit() { }

		void receive(CanMessage& msg);

	private:

        /**
         * Process incoming request for Tiny BMS
         * 
         * @param msg request
		 **/
		void _processTinyBmsRequest(CanMessage& msg);

        /**
         * Randomize values according to Tiny BMS parameter, and place values back
		 * into given data pointer
         * 
         * @param paramId 
		 * @param dataPtr
		 **/
		void _randomizeValues(uint8_t paramId, uint8_t* dataPtr);

        /**
         * Pack 4 8-bit ints with a float value
         * 
         * @param dataPtr to base address of ints
		 * @param value to pack
		 **/
		void _packFloat(uint8_t* dataPtr, float value);

        /**
         * Pack 2 8-bit ints with a 16-bit int in little endian order
         * 
         * @param dataPtr to base address of ints
		 * @param value to pack
		 **/
		void _packInt16(uint8_t* dataPtr, int16_t value);

        /**
         * Pack 4 8-bit ints with a 32-bit int in little endian order
         * 
         * @param dataPtr to base address of ints
		 * @param value to pack
		 **/
		void _packInt32(uint8_t* dataPtr, int32_t value);
};
