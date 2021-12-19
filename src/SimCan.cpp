#include "SimCan.h"

SimCan::SimCan() {
    _can = new mcp2515_can(CAN_CS_PIN);
}

SimCan::SimCan(Stream *serial, CanBehavior behavior) {
    _serial = serial;
    _can = new mcp2515_can(CAN_CS_PIN);
    _behavior = behavior;
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
        _behavior->transmit(_can);
    }

    // Listen for CAN messages
    if (_can->checkReceive() == CAN_MSGAVAIL) {
        _behavior->receive(_can);
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
