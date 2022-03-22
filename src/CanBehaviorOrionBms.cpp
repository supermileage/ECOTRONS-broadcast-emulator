#include "CanBehaviorOrionBms.h"

#define CAN_MSGLENGTH_ORIONBMS  8

void CanBehaviorOrionBms::transmit() {

    CanMessage msg;
    msg.dataLength = CAN_MSGLENGTH_ORIONBMS;

    msg.id = CAN_ORIONBMS_STATUS;
    _generateMsgStatus(msg.data);
    _generateMsgChecksum(msg.data);
    _sender->send(msg, "ORIONBMS STATUS");

    msg.id = CAN_ORIONBMS_PACK;
    _generateMsgPack(msg.data);
    _generateMsgChecksum(msg.data);
    _sender->send(msg, "ORIONBMS PACK");

    msg.id = CAN_ORIONBMS_CELL;
    _generateMsgCell(msg.data);
    _generateMsgChecksum(msg.data);
    _sender->send(msg, "ORIONBMS CELL");

    msg.id = CAN_ORIONBMS_TEMP;
    _generateMsgTemp(msg.data);
    _generateMsgChecksum(msg.data);
    _sender->send(msg, "ORIONBMS TEMP");

}

void CanBehaviorOrionBms::_generateMsgStatus(uint8_t* dataPtr) {

    // Relay Status
    dataPtr[0] = random(0,3);

    // Fault Codes
    // If both relays are not on, generate a random set of fault codes
    if(dataPtr[0] < 3) {
        dataPtr[1] = random(1,255);
        dataPtr[2] = random(1,255);
        dataPtr[3] = random(1,31);
    // If both relays are on, do not set a fault
    } else {
        dataPtr[1] = 0x0;
        dataPtr[2] = 0x0;
        dataPtr[3] = 0x0;
    }

    // Unused Bytes
    dataPtr[4] = 0x0;
    dataPtr[5] = 0x0;

    // Rolling Counter
    dataPtr[6] = _rollingCounterStatus++;

}

void CanBehaviorOrionBms::_generateMsgPack(uint8_t* dataPtr) {

    // Pack Voltage: 27.5 - 46.2 V
    _packInt16(dataPtr, random(275,462));
    // Pack Current: -12.0 - 120.0 A
    _packInt16(dataPtr + 2, random(-120,1200));
    // Pack SOC: 0.0 - 100.0 %
    dataPtr[4] = random(0,200);

    // Unused Byte
    dataPtr[5] = 0x0;

    // Rolling Counter
    dataPtr[6] = _rollingCounterPack++;

}

void CanBehaviorOrionBms::_generateMsgCell(uint8_t* dataPtr) {

    // Low Cell Voltage: 2.500 - 3.200 V
    _packInt16(dataPtr, random(2500,3200));
    // High Cell Voltage: 3.700 - 4.200 V
    _packInt16(dataPtr + 2, random(3700,4200));
    // Avg Cell Voltage: 3.200 - 3.700 V
    _packInt16(dataPtr + 4, random(3200,3700));

    // Rolling Counter
    dataPtr[6] = _rollingCounterCell++;

}

void CanBehaviorOrionBms::_generateMsgTemp(uint8_t* dataPtr) {

    // Pack Temp Low: -10 - 30 DegC
    dataPtr[0] = random(-10,30);
    // Pack Temp High: 40 - 100 DegC
    dataPtr[1] = random(40,100);
    // Pack Temp Avg: 30 - 40 DegC
    dataPtr[2] = random(30,40);
    // BMS Temp: 0 - 40 DegC
    dataPtr[3] = random(0,40);

    // Unused Bytes
    dataPtr[4] = 0x0;
    dataPtr[5] = 0x0;

    // Rolling Counter
    dataPtr[6] = _rollingCounterTemp++;

}

void CanBehaviorOrionBms::_generateMsgChecksum(uint8_t* dataPtr) {
    uint8_t checksum = 0;

    for(int i = 0; i < CAN_MSGLENGTH_ORIONBMS - 1; i++) {
        checksum += dataPtr[i];
    }

    dataPtr[7] = checksum;

}

void CanBehaviorOrionBms::_packInt16(uint8_t* dataPtr, int16_t value) {
    dataPtr[0] = value >> 8;
    dataPtr[1] = value;
}
