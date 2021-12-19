#include "CanBmsBehavior.h"

void CanBmsBehavior::transmit(mcp2515_can* can) {
    for(CanMessage msg : BMS_MSGS){
        uint8_t error = can->sendMsgBuf(msg.id, CAN_FRAME, msg.dataLength, msg.data);
        if(_serial){
            _serial->print("CAN MESSAGE SENT - ID: 0x"); 
            _serial->print(msg.id, HEX); 
            _serial->println(" - Status: " + SimCan::getErrorDescription(error));
        }
    }
}

void CanBmsBehavior::receive(mcp2515_can* can){
    uint8_t len = 0;
    uint8_t buf[8];

    can->readMsgBuf(&len, buf); 

    uint16_t canId = can->getCanId();

    if(canId == BMS_REQUEST_ID){
        _processBmsRequest(can, len, buf);
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

void CanBmsBehavior::_processBmsRequest(mcp2515_can* can, uint8_t len, uint8_t buf[]){

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
                _serial->println(" - Status: " + SimCan::getErrorDescription(error));
            }
        }
    }

    if(!reqFulfilled && _serial){
        _serial->println("ERROR: BMS PROPERTY NOT RECOGNIZED!");
    }
}