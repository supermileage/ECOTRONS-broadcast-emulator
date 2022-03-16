#include "CanBehaviorSteeringHelper.h"

#define TIME_TO_COUNT_MESSAGES 1000

const String accessoryNames[] = { "Headlights", "Brakelights", "Horn", "Harzards", "Blinker_R", "Blinker_L", "Wipers" };
const String readyNames[] = { "Ignition", "Dms", "Brake" };


CanBehaviorSteeringHelper::CanBehaviorSteeringHelper() {
	_lastReceiveTime = millis();
}

void CanBehaviorSteeringHelper::transmit() {
	_sender->send({ CAN_TELEMETRY_GPS_DATA, 0x1, { (uint8_t)((millis() / 1000) % 255) } }, String(""));

	CanMessage msg = { CAN_TELEMETRY_BMS_DATA, 0x4, { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } };
	float someValue = (float)random(0, 43);
	memcpy((void*)msg.data, (void*)&someValue, 4);
	_sender->send(msg, "");
}

void CanBehaviorSteeringHelper::receive(CanMessage& msg) {
	if (msg.id == CAN_STEERING_THROTTLE) {
		++_receivedMessageCount;
	}

	// every second, we tally throttle updates we've received from steering
	if (millis() - _lastReceiveTime >= TIME_TO_COUNT_MESSAGES) {
		_lastReceiveTime = millis();
		Serial.println("Received " + String(_receivedMessageCount) + " messages in the past second");
		_receivedMessageCount = 0;
	}

	// // print can accessories operation messages
	// if (msg.id == CAN_ACC_OPERATION) {
	// 	unsigned char data = msg.data[1];
	// 	for (int i = 0; i < 7; i++) {
	// 		Serial.print(accessoryNames[i] + ": " + String((data >> i) & 1)  + " -- ");
	// 	}
	// 	Serial.println("");
	// }

	// // print can steering ready messages
	// if (msg.id == CAN_STEERING_READY) {
	// 	unsigned char data = msg.data[0];
	// 	for (int i = 0; i < 3; i++) {
	// 		Serial.print(readyNames[i] + ": " + String((data >> i) & 1)  + " -- ");
	// 	}
	// 	Serial.println("");
	// }
}