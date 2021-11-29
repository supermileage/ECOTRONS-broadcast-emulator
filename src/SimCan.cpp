#include "SimCan.h"

SimCan::SimCan() {
    _can = new mcp2515_can(CAN_CS_PIN);
}

SimCan::SimCan(Stream *serial) {
    _serial = serial;
    _can = new mcp2515_can(CAN_CS_PIN);
}

void SimCan::begin(){
    // CAN begin
    SPI.begin();
    uint8_t error = _can->begin(CAN_500KBPS,MCP_8MHz);

    if(_serial){
        _serial->println("CAN Init Status: " + _getErrorDescription(error));
    }

    _last_transmit = millis();
}

void SimCan::handle(){
    // Send CAN Messages
    if (millis() - _last_transmit >= CAN_TRANSMIT_INTERVAL) {
        _last_transmit = millis();
        _transmit();
    } 

    // Listen for CAN messages
    if (_can->checkReceive() == CAN_MSGAVAIL) {
        _receive();
    }

}

void SimCan::_transmit() {
        for(CanMessage msg : TRANSMIT_MSGS){
            uint8_t error = _can->sendMsgBuf(msg.id, CAN_FRAME, msg.dataLength, msg.data);
            if(_serial){
                _serial->print("CAN MESSAGE SENT - ID: 0x"); 
                _serial->print(msg.id, HEX); 
                _serial->println(" - Status: " + _getErrorDescription(error));
            }
        }

}

void SimCan::_receive(){
    uint8_t len = 0;
    uint8_t buf[8];

    _can->readMsgBuf(&len, buf); 

    uint16_t canId = _can->getCanId();

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

void SimCan::_processBmsRequest(uint8_t len, uint8_t buf[]){

    if(_serial) _serial->println("BMS CAN REQUEST RECEIVED!");
    
    // Check to make sure request length is correct
    if (len != 8 && _serial){
        _serial->println("ERROR: BMS CAN REQUEST TOO SHORT!");
    }

    bool reqFulfilled = false;
    // Check all the BMS properties that we're interested in and see if the first byte matches its id
    for(uint8_t i = 0; i < NUM_BMS_PROPERTIES; i++){
        if(buf[0] == BMS_PROPERTY[i]){
            reqFulfilled = true;
            // Create a response
            uint8_t response[6];
            // First byte is 0x01 to indicate OK
            response[0] = 0x01;
            // Second byte is the BMS property id
            response[1] = BMS_PROPERTY[i];
            // Next 2-4 bytes are the data
            for(uint8_t j = 0; j < BMS_RESPONSE_LENGTH[i]; j++){
                response[j+2] = BMS_RESPONSE_DATA[i][j];
            }
            // Send the message
            uint8_t error = _can->sendMsgBuf(BMS_RESPONSE_ID, CAN_FRAME, BMS_RESPONSE_LENGTH[i]+2, response);
            if(_serial){
                _serial->println("BMS RESPONSE SENT - PROPERTY: " + String(BMS_PROPERTY[i]) + " - Status: " + _getErrorDescription(error));
            }
        }
    }

    if(!reqFulfilled && _serial){
        _serial->println("ERROR: BMS PROPERTY NOT RECOGNIZED!");
    }
}

String SimCan::getHumanName() {
    return "CAN";
}

String SimCan::_getErrorDescription(uint8_t errorCode){
    switch(errorCode){
        case CAN_OK: 
            return "CAN OK";
            break;
        case CAN_FAILINIT:
            return "CAN FAIL INIT";
            break;
        case CAN_FAILTX:
            return "CAN FAIL TX";
            break;
        case CAN_MSGAVAIL:
            return "CAN MSG AVAIL";
            break;
        case CAN_NOMSG:
            return "CAN NO MSG";
            break;
        case CAN_CTRLERROR:
            return "CAN CTRL ERROR";
            break;
        case CAN_GETTXBFTIMEOUT:
            return "CAN TX BF TIMEOUT";
            break;
        case CAN_SENDMSGTIMEOUT:    
            return "CAN SEND MSG TIMEOUT";
            break;
        default:
            return "CAN FAIL";
            break;
    }
}
