#include "CanBehaviorBms.h"

// BMS Settings
#define BMS_REQUEST_ID      0x201
#define BMS_RESPONSE_ID     0x241
#define BMS_REQUEST_LENGTH  8

const CanMessage BMS_RESPONSE[] =   {{BMS_RESPONSE_ID, 6, {0x01,0x14,0x00,0x00,0x40,0x42}}, // Pack Voltage         - 48.0
                                    {BMS_RESPONSE_ID, 6, {0x01,0x15,0xCD,0xCC,0x4C,0x3F}},  // Pack Current         - 0.8
                                    {BMS_RESPONSE_ID, 4, {0x01,0x16,0x04,0x10}},            // Max Cell Voltage     - 4100
                                    {BMS_RESPONSE_ID, 4, {0x01,0x17,0xD8,0x0E}},            // Min Cell Voltage     - 3800
                                    {BMS_RESPONSE_ID, 4, {0x01,0x18,0x93,0x00}},            // Current Status       - DISCHARGING
                                    {BMS_RESPONSE_ID, 6, {0x01,0x1A,0xC0,0x9E,0xE6,0x05}},  // State of Charge      - 99000000
                                    {BMS_RESPONSE_ID, 6, {0x01,0x1B,0xFA,0x00,0x00,0x00}},       // Internal Temperature - 250
                                    {BMS_RESPONSE_ID, 6, {0x01,0x1B,0x04,0x01,0x00,0x01}},       // Battery Temp #1      - 260
                                    {BMS_RESPONSE_ID, 6, {0x01,0x1B,0x18,0x01,0x00,0x02}}};      // Battery Temp #2      - 280

void CanBehaviorBms::receive(CanMessage& msg) {
    if(msg.id == BMS_REQUEST_ID){
        _processBmsRequest(msg);
    }
}

void CanBehaviorBms::_processBmsRequest(CanMessage& msg){
    if(DEBUG_SERIAL) Serial.println("BMS CAN REQUEST RECEIVED!");
    
    // Check to make sure request length is correct
    if (msg.dataLength != BMS_REQUEST_LENGTH && DEBUG_SERIAL){
        Serial.println("ERROR: BMS CAN REQUEST TOO SHORT!");
    }

    bool reqFulfilled = false;
    // Check all the BMS properties that we're interested in and see if the first byte matches its id
    for(CanMessage m : BMS_RESPONSE){
        if(msg.data[0] == m.data[1]){
            reqFulfilled = true;
            // Introduce a random delay from 0-4 ms
            delay(random(0,10));
            // Send the message
            _sender->send(m, String("BMS RESPONSE SENT"));
        }
    }

    if(!reqFulfilled && DEBUG_SERIAL){
        Serial.println("ERROR: BMS PROPERTY NOT RECOGNIZED!");
    }
}