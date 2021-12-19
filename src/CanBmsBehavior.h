#ifndef CAN_BMS_BEHAVIOR_H_
#define CAN_BMS_BEHAVIOR_H_

#include "CanBehavior.h"

// BMS Settings
#define BMS_REQUEST_ID      0x201
#define BMS_RESPONSE_ID     0x241
#define BMS_REQUEST_LENGTH  8

const CanMessage TEST1 = {0x14, 8, {0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
const CanMessage TEST2 = {0x2D, 8, {0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00}};
const CanMessage BMS_MSGS[] = {TEST1, TEST2};

const CanMessage BMS_RESPONSE[] =   {{BMS_RESPONSE_ID, 6, {0x14,0x01,0x00,0x00,0x40,0x42}}, // Pack Voltage         - 48.0
                                    {BMS_RESPONSE_ID, 6, {0x15,0x01,0xCD,0xCC,0x4C,0x3F}},  // Pack Current         - 0.8
                                    {BMS_RESPONSE_ID, 4, {0x16,0x01,0x04,0x10}},            // Max Cell Voltage     - 4100
                                    {BMS_RESPONSE_ID, 4, {0x17,0x01,0xD8,0x0E}},            // Min Cell Voltage     - 3800
                                    {BMS_RESPONSE_ID, 4, {0x18,0x01,0x93,0x00}},            // Current Status       - DISCHARGING
                                    {BMS_RESPONSE_ID, 6, {0x1A,0x01,0xC0,0x9E,0xE6,0x05}},  // State of Charge      - 99000000
                                    {BMS_RESPONSE_ID, 5, {0x1B,0x01,0xFA,0x00,0x00}},       // Internal Temperature - 250
                                    {BMS_RESPONSE_ID, 5, {0x1B,0x01,0x04,0x01,0x01}},       // Battery Temp #1      - 260
                                    {BMS_RESPONSE_ID, 5, {0x1B,0x01,0x18,0x01,0x02}}};      // Battery Temp #2      - 280

class CanBmsBehavior : public CanBehavior {
	public:
		CanBmsBehavior() { }

		void transmit(mcp2515_can* can);

		void receive(mcp2515_can* can);
	private:
		void _processBmsRequest(mcp2515_can* can, uint8_t len, uint8_t buf[]);
};

#endif