#include "CanUrbanAccessoriesBehavior.h"

const uint16_t ACCESSORIES_CAN_ID = 0x14;
const CanMessage TEST1 = {ACCESSORIES_CAN_ID, 8, {0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
const CanMessage TEST2 = {ACCESSORIES_CAN_ID, 8, {0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00}};
const CanMessage URBAN_MSGS[] = {TEST1, TEST2};

const int MIN_DATA_LENGTH = 0x2;
const int MAX_DATA_LENGTH = 0x8;
const int MIN_STATUS_ID = 0x0;
const int MAX_STATUS_ID = 0xA;

void CanUrbanAccessoriesBehavior::transmit(mcp2515_can* can) {
	for(CanMessage msg : URBAN_MSGS) {
		_randomizeMessage(msg);
        uint8_t error = can->sendMsgBuf(msg.id, CAN_FRAME, msg.dataLength, msg.data);
        if(_serial){
            _serial->print("CAN MESSAGE SENT - ID: 0x"); 
            _serial->print(msg.id, HEX); 
            _serial->println(" - Status: " + SimCan::getErrorDescription(error));
        }
    }
}

void CanUrbanAccessoriesBehavior::_randomizeMessage(CanMessage& message) {
	randomSeed(analogRead(0));

	message.dataLength = random(MIN_DATA_LENGTH, MAX_DATA_LENGTH);

	// randomize data byes in can message
	for (uint8_t i = 0; i < message.dataLength; i++) {
		char dataByte = random(MIN_STATUS_ID, MAX_STATUS_ID);
		message.data[i] = (dataByte << 1) + (dataByte % 2);
	}
}