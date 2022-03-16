#include "SimCan.h"

SimCan::SimCan() {
    _can = new mcp2515_can(CAN_CS_PIN);
}

SimCan::SimCan(CanBehavior** behaviors) {
    _can = new mcp2515_can(CAN_CS_PIN);
    _behaviors = behaviors;
    for (int i = 0; _behaviors[i]; i++) {
        _behaviors[i]->setSender(new SimCan::Sender(this));
    }  
}

void SimCan::begin(){
    // CAN begin
    SPI.begin();
    uint8_t error = _can->begin(CAN_500KBPS,MCP_8MHz);

    if(DEBUG_SERIAL){
        Serial.println("CAN Init Status: " + getErrorDescription(error));
    }

    _last_transmit = millis();
}

void SimCan::handle(){
    // Send CAN Messages
    if (millis() - _last_transmit >= CAN_TRANSMIT_INTERVAL){
        _last_transmit = millis();
        _transmit();
    }

    // Listen for CAN messages
    if (_can->checkReceive() == CAN_MSGAVAIL) {
        _receive();
    }
}

void SimCan::_transmit() {
    for (int i = 0; _behaviors[i]; i++) {
        _behaviors[i]->transmit();
    }  

}

void SimCan::_receive() {
    CanMessage message;
    message.dataLength = 0;
    _can->readMsgBuf(&message.dataLength, message.data); 
    message.id = _can->getCanId();
	_serialReceiveMessage(message);

    for (int i = 0; _behaviors[i]; i++) {
        _behaviors[i]->receive(message);
    }
}

String SimCan::getHumanName() {
    return "CAN";
}

void SimCan::send(CanMessage msg, String serialMsg) {
    uint8_t error = _can->sendMsgBuf(msg.id, CAN_FRAME, msg.dataLength, msg.data);
    _serialSendMessage(msg, error, serialMsg);
}

void SimCan::_serialSendMessage(const CanMessage& msg, uint8_t error, String serialMsg) {
    // if(DEBUG_SERIAL){
    //     Serial.print(serialMsg +  " - ID: 0x"); 
    //     Serial.print(msg.id, HEX); 
    //     Serial.println(" - Status: " + getErrorDescription(error));
    // }
}

void SimCan::_serialReceiveMessage(const CanMessage& msg) {
    // if(DEBUG_SERIAL){
    //     Serial.println("-----------------------------");
    //     Serial.print("CAN MESSAGE RECEIVED - ID: 0x");
    //     Serial.println(msg.id, HEX);

    //     for (int i = 0; i < msg.dataLength; i++) { // print the data
    //         Serial.print("0x");
    //         Serial.print(msg.data[i], HEX);
    //         Serial.print("\t");
    //     }
    //     Serial.println();
    // }
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

void SimCan::Sender::send(CanMessage msg, String serialMsg) {
    _owner->send(msg, serialMsg);
}