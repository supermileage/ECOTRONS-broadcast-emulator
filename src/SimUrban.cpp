#include "SimUrban.h"

#define CAN_DEBUG_BAUD_RATE     115200
#define CAN_CS_PIN              A5
#define CAN_SPEED               CAN_500KBPS
#define CAN_CONTROLLER_SPEED    MCP_8MHz

<<<<<<< HEAD:src/SimCan.cpp
SimCan::SimCan(CanBehavior** behaviors) {
    _can = new mcp2515_can(CAN_CS_PIN);
    _behaviors = behaviors;
    for (int i = 0; _behaviors[i]; i++) {
        _behaviors[i]->setSender(new SimCan::Sender(this));
    }  
=======
#define DEBUG_MSG_RECEIVE       1
#define DEBUG_MSG_SEND          1

void SimUrban::addBehavior(CanBehavior* behavior) {
    uint8_t counter = 0;
    while(_behaviors[counter] && counter < MAX_BEHAVIORS) {
        counter++;
    }
    _behaviors[counter] = behavior;
>>>>>>> master:src/SimUrban.cpp
}

void SimUrban::begin(){

    Serial.begin(CAN_DEBUG_BAUD_RATE);

    // CAN begin
    SPI.begin();

    _can = new mcp2515_can(CAN_CS_PIN);

    uint8_t error = _can->begin(CAN_SPEED, CAN_CONTROLLER_SPEED);

    Serial.println("CAN Init Status: " + getErrorDescription(error));

    for (int i = 0; _behaviors[i]; i++) {
        _behaviors[i]->setSender(new SimUrban::Sender(this));
    }  

    _lastUpdate = millis();
}

void SimUrban::handle(){
    // Send CAN Messages
    if (millis() - _lastUpdate >= _updateInterval){
        _lastUpdate = millis();
        _transmit();
    }

    // Listen for CAN messages
    if (_can->checkReceive() == CAN_MSGAVAIL) {
        _receive();
    }
}

<<<<<<< HEAD:src/SimCan.cpp
void SimCan::_transmit() {
=======
void SimUrban::send(CanMessage msg, String serialMsg) {
    uint8_t error = _can->sendMsgBuf(msg.id, CAN_FRAME, msg.dataLength, msg.data);
    
    if(DEBUG_MSG_SEND) {
        Serial.print(serialMsg +  " SEND - ID: 0x"); 
        Serial.print(msg.id, HEX); 
        Serial.println(" - Status: " + getErrorDescription(error));

        for (int i = 0; i < msg.dataLength; i++) { // print the data
            Serial.print("0x");
            Serial.print(msg.data[i], HEX);
            Serial.print("\t");
        }

        Serial.println();
    }
}

void SimUrban::_transmit() {
>>>>>>> master:src/SimUrban.cpp
    for (int i = 0; _behaviors[i]; i++) {
        _behaviors[i]->transmit();
    }  

}

void SimUrban::_receive() {
    CanMessage message;
    message.dataLength = 0;
    _can->readMsgBuf(&message.dataLength, message.data); 
    message.id = _can->getCanId();
	_serialReceiveMessage(message);

    for (int i = 0; _behaviors[i]; i++) {
        _behaviors[i]->receive(message);
    }
<<<<<<< HEAD:src/SimCan.cpp
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
=======

    if(DEBUG_MSG_RECEIVE) {

        Serial.println("-----------------------------");
        Serial.print("CAN MESSAGE RECEIVED - ID: 0x");
        Serial.println(message.id, HEX);

        for (int i = 0; i < message.dataLength; i++) { // print the data
            Serial.print("0x");
            Serial.print(message.data[i], HEX);
            Serial.print("\t");
        }
        Serial.println();
    }

>>>>>>> master:src/SimUrban.cpp
}

String SimUrban::getErrorDescription(uint8_t errorCode){
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

void SimUrban::Sender::send(CanMessage msg, String serialMsg) {
    _owner->send(msg, serialMsg);
}