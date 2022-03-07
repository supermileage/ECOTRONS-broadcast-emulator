#include "CanBehaviorUrbanAccessories.h"

const uint16_t ACCESSORIES_STATUS_ID = 0x71;
const uint16_t ACCESSORIES_OP_ID = 0x60;
const CanMessage TEST1 = {ACCESSORIES_STATUS_ID, 8, {0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
const CanMessage TEST2 = {ACCESSORIES_STATUS_ID, 8, {0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00}};
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

bool CanBehaviorUrbanAccessories::_messageContainsId(CanMessage& message, byte id, byte& index) {
	for (byte i = 1; i < message.dataLength; i++) {
		if ((message.data[i] >> 1) == id) {
			index = i;
			return true;
		}
	}
	return false;
}

void CanBehaviorUrbanAccessories::receive(CanMessage& msg) {
	if (msg.id == ACCESSORIES_OP_ID) {
		for (byte i = 0; i < 7; i++) {
			byte index = 0;
			if (_messageContainsId(msg, i, index)) {
				Serial.print(msg.data[index] & 0x1 ? "O\t" : "|\t");
			} else {
				Serial.print("\t");
			}
		}
		Serial.print("\n");
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