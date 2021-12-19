#include "UrbanAccessoriesBehavior.h"

void UrbanAccessoriesBehavior::transmit(mcp2515_can can) {
	_randomizeMessages();

	for(CanMessage msg : URBAN_MSGS) {
        uint8_t error = _can->sendMsgBuf(msg.id, CAN_FRAME, msg.dataLength, msg.data);
        if(_serial){
            _serial->print("CAN MESSAGE SENT - ID: 0x"); 
            _serial->print(msg.id, HEX); 
            _serial->println(" - Status: " + _getErrorDescription(error));
        }
    }
}

void UrbanAccessoriesBehavior::_randomizeMessages() {

}