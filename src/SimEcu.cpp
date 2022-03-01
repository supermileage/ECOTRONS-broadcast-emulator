#include "SimEcu.h"

SimEcu::SimEcu(Stream *serial) {
    _serial = serial;
}

void SimEcu::begin(){
    _ecu_data[0] = ECU_HEADER_1;
    _ecu_data[1] = ECU_HEADER_2;
    _ecu_data[2] = ECU_HEADER_3;
    _ecu_data[3] = ECU_DATA_FIELD_LENGTH;
    _ecu_data[4] = ECU_SERVICE_ID;

    _ecu_last_update = millis();
}

void SimEcu::handle(){
    if (millis() - _ecu_last_update >= ECU_UPDATE_MS) {
        _ecu_last_update = millis();
        _randomizeData();
        _calculateChecksum();

        for (int i = 0; i < ECU_PACKET_SIZE; i++) {
            _serial->write(_ecu_data[i]);
        }
        
    } 
}

String SimEcu::getHumanName() {
    return "ECU";
}

void SimEcu::_randomizeData() {

    for (int i = 5; i < ECU_PACKET_SIZE - 1; i++) {
        uint8_t value = random(0, 255);
        _ecu_data[i] = value;
    }


}

void SimEcu::_calculateChecksum() {

    uint8_t checksum = 0;

    for(uint8_t i = 0; i < ECU_PACKET_SIZE - 1; i++) {
        checksum += _ecu_data[i];
    }

    _ecu_data[ECU_PACKET_SIZE - 1] = checksum;

}