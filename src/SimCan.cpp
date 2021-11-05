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
        _serial->println("CAN Init Status: " + getErrorDescription(error));
    }

    _can_last_update = millis();
}

void SimCan::handle(){
    // Send CAN Messages
    if (millis() - _can_last_update >= CAN_UPDATE_MS) {
        _can_last_update = millis();
        uint8_t error1 = _can->sendMsgBuf(CAN0_ID, CAN_FRAME, CAN0_DATA_LENGTH, _can0_data);  
        uint8_t error2 = _can->sendMsgBuf(CAN1_ID, CAN_FRAME, CAN1_DATA_LENGTH, _can1_data);  
        
        if(_serial){
            _serial->println("CAN Msg 1 Status: " + getErrorDescription(error1));
            _serial->println("CAN Msg 2 Status: " + getErrorDescription(error2));
        }
    } 

    // Print any CAN messages received (debug mode only)
    if(_serial){
        unsigned char len = 0;
        unsigned char buf[8];

        if (_can->checkReceive() == CAN_MSGAVAIL) {
            _can->readMsgBuf(&len, buf); 

            unsigned long canId = _can->getCanId();

            _serial->println("-----------------------------");
            _serial->print("Get data from ID: 0x");
            _serial->println(canId, HEX);

            for (int i = 0; i < len; i++) { // print the data
                _serial->print(buf[i], HEX);
                _serial->print("\t");
            }
            _serial->println();
        }
    }
}

String SimCan::getHumanName() {
    return "CAN";
}

String SimCan::getErrorDescription(uint8_t errorCode){
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
