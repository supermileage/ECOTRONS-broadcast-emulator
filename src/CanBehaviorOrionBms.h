#pragma once

#include "CanBehavior.h"

class CanBehaviorOrionBms : public CanBehavior {

	public:

		CanBehaviorOrionBms() {}

		void transmit();

		void receive(CanMessage& msg) {}

    private:

        uint8_t _rollingCounterStatus = 0;
        uint8_t _rollingCounterPack= 0;
        uint8_t _rollingCounterCell = 0;
        uint8_t _rollingCounterTemp = 0;

        /**
         * Generate random values for status message
         * 
		 * @param dataPtr pointer to data bytes
		 **/
        void _generateMsgStatus(uint8_t* dataPtr);

        /**
         * Generate random values for pack message
         * 
		 * @param dataPtr pointer to data bytes
		 **/
        void _generateMsgPack(uint8_t* dataPtr);

        /**
         * Generate random values for cell message
         * 
		 * @param dataPtr pointer to data bytes
		 **/
        void _generateMsgCell(uint8_t* dataPtr);

        /**
         * Generate random values for temperature message
         * 
		 * @param dataPtr pointer to data bytes
		 **/
        void _generateMsgTemp(uint8_t* dataPtr);

        /**
         * Generate checksum of message
         * 
		 * @param dataPtr pointer to data bytes
		 **/
        void _generateMsgChecksum(uint8_t* dataPtr);

        /**
         * Pack 2 8-bit ints with a 16-bit int in big endian order
         * 
         * @param dataPtr to base address of ints
		 * @param value to pack
		 **/
        void _packInt16(uint8_t* dataPtr, int16_t value);
};