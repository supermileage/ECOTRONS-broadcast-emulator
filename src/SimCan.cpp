#include "SimCan.h"

SimCan::SimCan() {
    _can = new mcp2515_can(CAN_CS_PIN);
}

void SimCan::begin(){
    // CAN begin
    SPI.begin();
    _can->begin(CAN_125KBPS,MCP_8MHz);

    _can_last_update = millis();
}

void SimCan::handle(){
    // Check for and send CAN update
    if (millis() - _can_last_update >= CAN_UPDATE_MS) {
        _can_last_update = millis();
        _can->sendMsgBuf(CAN0_ID, CAN_FRAME, CAN0_DATA_LENGTH, _can0_data);  
        _can->sendMsgBuf(CAN1_ID, CAN_FRAME, CAN1_DATA_LENGTH, _can1_data);  
    } 
}

String SimCan::getHumanName() {
    return "CAN";
}
