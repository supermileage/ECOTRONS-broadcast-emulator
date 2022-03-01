#include "CanBehaviorUrbanAccessories.h"

const uint16_t ACCESSORIES_CAN_ID = 0x71;
const CanMessage TEST1 = {ACCESSORIES_CAN_ID, 8, {0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
const CanMessage TEST2 = {ACCESSORIES_CAN_ID, 8, {0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00}};
const CanMessage URBAN_MSGS[] = {TEST1, TEST2};

const int MIN_DATA_LENGTH = 0x2;
const int MAX_DATA_LENGTH = 0x8;
const int MIN_STATUS_ID = 0x0;
const int MAX_STATUS_ID = 0x8;

void CanBehaviorUrbanAccessories::transmit() {
	for(CanMessage msg : URBAN_MSGS) {
		_randomizeMessage(msg);
        _sender->send(msg, String("CAN MESSAGE SENT"));
    }
}

void CanBehaviorUrbanAccessories::_randomizeMessage(CanMessage& message) {
	message.dataLength = random(MIN_DATA_LENGTH, MAX_DATA_LENGTH);

	// randomize data byes in can message
	for (uint8_t i = 0; i < message.dataLength; i++) {
		char dataByte = random(MIN_STATUS_ID, MAX_STATUS_ID);
		message.data[i] = (dataByte << 1) + random(0, 2);
	}
}