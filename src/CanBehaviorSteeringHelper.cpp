#include "CanBehaviorSteeringHelper.h"

#define DEBUG_MOTOR_CTRL_MESSAGES 		0
#define MESSAGE_COUNTING_INTERVAL 		1000
#define DEBUG_READY_MESSAGES 			0
#define DEBUG_ACCESSORIES_MESSAGES 		0
#define SEND_MOCK_VALUES_TO_STEERING 	0

const String accessoryNames[] = { "Headlights", "Brakelights", "Horn", "Harzards", "Blinker_R", "Blinker_L", "Wipers" };
const String readyNames[] = { "Ignition", "Dms", "Brake" };

CanBehaviorSteeringHelper::CanBehaviorSteeringHelper() {
	_lastReceiveTime = millis();
}

void CanBehaviorSteeringHelper::transmit() {
	#if SEND_MOCK_VALUES_TO_STEERING
	_sender->send({ CAN_TELEMETRY_GPS_DATA, 0x1, { (uint8_t)((millis() / 1000) % 255) } }, String(""));

	CanMessage msg = { CAN_TELEMETRY_BMS_DATA, 0x4, { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } };
	float someValue = (float)random(0, 43);
	memcpy((void*)msg.data, (void*)&someValue, 4);
	_sender->send(msg, "");
	#endif
}

void CanBehaviorSteeringHelper::receive(CanMessage& msg) {
	#if DEBUG_MOTOR_CTRL_MESSAGES
	if (msg.id == CAN_STEERING_THROTTLE) {
		++_receivedMessageCount;
	}
	if (millis() - _lastReceiveTime >= TIME_TO_COUNT_MESSAGES) {
		_lastReceiveTime = millis();
		Serial.println("Received " + String(_receivedMessageCount) + " messages in the past second");
		_receivedMessageCount = 0;
	}
	#endif

	#if DEBUG_READY_MESSAGES
	if (msg.id == CAN_STEERING_READY) {
		unsigned char data = msg.data[0];
		for (int i = 0; i < 3; i++) {
			Serial.print(readyNames[i] + ": " + String((data >> i) & 1)  + " -- ");
		}
		Serial.println("");
	}
	#endif

	#if DEBUG_ACCESSORIES_MESSAGES
	if (msg.id == CAN_ACC_OPERATION && msg.data[0] == 0) {
		unsigned char data = msg.data[1];
		for (int i = 0; i < 7; i++) {
			Serial.print(accessoryNames[i] + ": " + String((data >> i) & 1)  + " -- ");
		}
		Serial.println("");
	}

	if (msg.id == CAN_ACC_OPERATION && msg.data[0] == 2) {
		Serial.print("Received -- R_Blinker: " + String(msg.data[1] & 1) + " -- L_Blinker: " + String(msg.data[2] & 1));
		Serial.println("");
	}
	#endif
}