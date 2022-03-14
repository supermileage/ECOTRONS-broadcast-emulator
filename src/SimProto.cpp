#include "SimProto.h"

#define ECU_BAUD_RATE           115200

#define ECU_HEADER_1            0x80
#define ECU_HEADER_2            0x8F
#define ECU_HEADER_3            0xEA
#define ECU_DATA_FIELD_LENGTH   0x16
#define ECU_SERVICE_ID          0x50

#define OFFSET_RPM              0x06
#define OFFSET_MAP              0x08
#define OFFSET_TPS              0x0A
#define OFFSET_ECT              0x0C
#define OFFSET_IAT              0x0E
#define OFFSET_O2S              0x10
#define OFFSET_SPARK            0x12
#define OFFSET_FUELPW1          0x14
#define OFFSET_FUELPW2          0x16
#define OFFSET_UBADC            0x18

void SimProto::begin(){
    Serial.begin(ECU_BAUD_RATE, SERIAL_8N1);

    _ecuData[0] = ECU_HEADER_1;
    _ecuData[1] = ECU_HEADER_2;
    _ecuData[2] = ECU_HEADER_3;
    _ecuData[3] = ECU_DATA_FIELD_LENGTH;
    _ecuData[4] = ECU_SERVICE_ID;

}

void SimProto::handle(){
    if (millis() - _lastUpdate >= _updateInterval) {
        _lastUpdate = millis();
        _randomizeData();
        _calculateChecksum();

        for (int i = 0; i < ECU_PACKET_SIZE; i++) {
            Serial.write(_ecuData[i]);
        }
        
    } 
}

void SimProto::_randomizeData() {

    // RPM
    // Range: 0 - 10,000
    _packValue(_ecuData + OFFSET_RPM, random(0,10000) * 4);

    // MAP
    // Range: 0 - 100 kPa
    _packValue(_ecuData + OFFSET_MAP, random(0,100) * 256);

    // TPS
    // Range: 0 - 100%
    _packValue(_ecuData + OFFSET_TPS, random(0,100) * 666);

    // ECT
    // Range: -10 - 100 DegC
    _packValue(_ecuData + OFFSET_ECT, random(-10,100) + 40);

    // IAT
    // Range: -10 - 100 DegC
    _packValue(_ecuData + OFFSET_IAT, random(-10,100) + 40);

    // O2S
    // Range: 0 - 5 V
    _packValue(_ecuData + OFFSET_O2S, random(0,5) * 208);

    // SPARK
    // Range: 0 - 360 Deg
    _packValue(_ecuData + OFFSET_SPARK, random(0,360) * 2);

    // FUELPW1
    // Range: 0 - 60ms
    _packValue(_ecuData + OFFSET_FUELPW1, random(0,60) * 1000);

    // FUELPW2
    // Range: 0 - 60ms
    _packValue(_ecuData + OFFSET_FUELPW2, random(0,60) * 1000);

    // UBADC
    // Range: 0 - 14 V
    _packValue(_ecuData + OFFSET_MAP, random(0,14) * 160);

}

void SimProto::_calculateChecksum() {

    uint8_t checksum = 0;

    for(uint8_t i = 0; i < ECU_PACKET_SIZE - 1; i++) {
        checksum += _ecuData[i];
    }

    _ecuData[ECU_PACKET_SIZE - 1] = checksum;

}

void SimProto::_packValue(uint8_t* dataPtr, int16_t value) {
    dataPtr[0] = value >> 8;
    dataPtr[1] = value;
}