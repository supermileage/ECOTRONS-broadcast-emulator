#include "CanBmsBehavior.h"

// BMS Settings
#define BMS_REQUEST_ID      0x201
#define BMS_RESPONSE_ID     0x241
#define BMS_REQUEST_LENGTH  8

const CanMessage BMS_RESPONSE[] =   {{BMS_RESPONSE_ID, 6, {0x14,0x01,0x00,0x00,0x40,0x42}}, // Pack Voltage         - 48.0
                                    {BMS_RESPONSE_ID, 6, {0x15,0x01,0xCD,0xCC,0x4C,0x3F}},  // Pack Current         - 0.8
                                    {BMS_RESPONSE_ID, 4, {0x16,0x01,0x04,0x10}},            // Max Cell Voltage     - 4100
                                    {BMS_RESPONSE_ID, 4, {0x17,0x01,0xD8,0x0E}},            // Min Cell Voltage     - 3800
                                    {BMS_RESPONSE_ID, 4, {0x18,0x01,0x93,0x00}},            // Current Status       - DISCHARGING
                                    {BMS_RESPONSE_ID, 6, {0x1A,0x01,0xC0,0x9E,0xE6,0x05}},  // State of Charge      - 99000000
                                    {BMS_RESPONSE_ID, 5, {0x1B,0x01,0xFA,0x00,0x00}},       // Internal Temperature - 250
                                    {BMS_RESPONSE_ID, 5, {0x1B,0x01,0x04,0x01,0x01}},       // Battery Temp #1      - 260
                                    {BMS_RESPONSE_ID, 5, {0x1B,0x01,0x18,0x01,0x02}}};      // Battery Temp #2      - 280

void SimCan::_transmit(mcp2515_can can) {
    for(CanMessage msg : TRANSMIT_MSGS){
        uint8_t error = can->sendMsgBuf(msg.id, CAN_FRAME, msg.dataLength, msg.data);
        if(_serial){
            _serial->print("CAN MESSAGE SENT - ID: 0x"); 
            _serial->print(msg.id, HEX); 
            _serial->println(" - Status: " + _getErrorDescription(error));
        }
    }
}

void CanBmsBehavior::receive(mcp2515_can can){
    uint8_t len = 0;
    uint8_t buf[8];

    can->readMsgBuf(&len, buf); 

    uint16_t canId = can->getCanId();

    if(canId == BMS_REQUEST_ID){
        _processBmsRequest(len, buf);
    }

    if(_serial){
        _serial->println("-----------------------------");
        _serial->print("CAN MESSAGE RECEIVED - ID: 0x");
        _serial->println(canId, HEX);

        for (int i = 0; i < len; i++) { // print the data
            _serial->print("0x");
            _serial->print(buf[i], HEX);
            _serial->print("\t");
        }
        _serial->println();
    }
}

void CanBmsBehavior::_processBmsRequest(uint8_t len, uint8_t buf[]){

    if(_serial) _serial->println("BMS CAN REQUEST RECEIVED!");
    
    // Check to make sure request length is correct
    if (len != BMS_REQUEST_LENGTH && _serial){
        _serial->println("ERROR: BMS CAN REQUEST TOO SHORT!");
    }

    bool reqFulfilled = false;
    // Check all the BMS properties that we're interested in and see if the first byte matches its id
    for(CanMessage m : BMS_RESPONSE){
        if(buf[0] == m.data[0]){
            reqFulfilled = true;
            // Introduce a random delay from 0-4 ms
            delay(random(0,4));
            // Send the message
            uint8_t error = can->sendMsgBuf(BMS_RESPONSE_ID, CAN_FRAME, m.dataLength, m.data);
            if(_serial){
                _serial->print("BMS RESPONSE SENT - PROPERTY: 0x"); 
                _serial->print(m.data[0], HEX);
                _serial->println(" - Status: " + _getErrorDescription(error));
            }
        }
    }

    if(!reqFulfilled && _serial){
        _serial->println("ERROR: BMS PROPERTY NOT RECOGNIZED!");
    }
}