#include "CanBehaviorTinyBms.h"

// BMS Settings
#define BMS_REQUEST_LENGTH          8
#define BMS_RESPONSE_DATA_OFFSET    2

#define PARAM_ID_EVENTS             0x11
#define PARAM_ID_PACK_VOLTAGE       0x14
#define PARAM_ID_PACK_CURRENT       0x15
#define PARAM_ID_CELL_VOLTAGE_MAX   0x16
#define PARAM_ID_CELL_VOLTAGE_MIN   0x17
#define PARAM_ID_STATUS             0x18
#define PARAM_ID_SOC                0x1A
#define PARAM_ID_TEMP               0x1B

#define NUM_PARAM_IDS               8

const uint8_t PARAM_IDS[NUM_PARAM_IDS] = {
    PARAM_ID_EVENTS,
    PARAM_ID_PACK_VOLTAGE,
    PARAM_ID_PACK_CURRENT,
    PARAM_ID_CELL_VOLTAGE_MAX,
    PARAM_ID_CELL_VOLTAGE_MIN,
    PARAM_ID_STATUS,
    PARAM_ID_SOC,
    PARAM_ID_TEMP};

const uint8_t PARAM_LENGTHS[NUM_PARAM_IDS] = {
    8,
    6, 
    6, 
    4, 
    4, 
    4, 
    6, 
    6};

void CanBehaviorTinyBms::receive(CanMessage& msg){
    if(msg.id == CAN_TINYBMS_REQUEST){
        _processTinyBmsRequest(msg);
    }
}

void CanBehaviorTinyBms::_processTinyBmsRequest(CanMessage& msg){
   
    // Check to make sure request length is correct
    if (msg.dataLength != BMS_REQUEST_LENGTH){
        Serial.println("ERROR: TINYBMS CAN REQUEST TOO SHORT!");
    }

    bool reqFulfilled = false;
    // Check all the BMS properties that we're interested in and see if the first byte matches its id
    for(int i = 0; i < NUM_PARAM_IDS ; i++){
        if(msg.data[0] == PARAM_IDS[i]){
            reqFulfilled = true;
            // Introduce a random delay from 0-4 ms
            delay(random(0,4));

            CanMessage reply;
            reply.id = CAN_TINYBMS_RESPONSE;
            reply.dataLength = PARAM_LENGTHS[i];
            reply.data[0] = 0x01;
            reply.data[1] = PARAM_IDS[i];

            // Send the message
            _randomizeValues(PARAM_IDS[i], reply.data + BMS_RESPONSE_DATA_OFFSET);
            _sender->send(reply, String("TINYBMSBMS RESPONSE SENT"));
        }
    }

    if(!reqFulfilled){
        Serial.println("ERROR: TINYBMSBMS PROPERTY NOT RECOGNIZED!");
    }
}

void CanBehaviorTinyBms::_randomizeValues(uint8_t paramId, uint8_t* dataPtr) {
    switch(paramId) {
        case PARAM_ID_EVENTS: {
            // Range: 0x00 - 0x7D
            int32_t value = random(0x00, 0x7D);
            _packInt32(dataPtr + 1, value);
            dataPtr[5] = 1;
            break;
        }
        case PARAM_ID_PACK_VOLTAGE: {
            // Range: 27.500 - 46.200
            int32_t value = random(27500, 46200);
            _packFloat(dataPtr, static_cast<float>(value) / 1000.0);
            break;
        }
        case PARAM_ID_PACK_CURRENT: {
            // Range: -120.000 - 13.000
            int32_t value = random(-120000, 12000);
            _packFloat(dataPtr, static_cast<float>(value) / 1000.0);
            break;
        }
        case PARAM_ID_CELL_VOLTAGE_MAX: {
            // Range: 3.700 - 4.200
            int32_t value = random(3700, 4200);
            _packInt16(dataPtr, value);
            break;
        }
        case PARAM_ID_CELL_VOLTAGE_MIN: {
            // Range: 2.500 - 3.699
            int32_t value = random(2500, 3699);
            _packInt16(dataPtr, value);
            break;
        }
        case PARAM_ID_STATUS: {
            // Range: 0x91 - 0x9B
            int32_t value = random(0x91, 0x9B);
            _packInt16(dataPtr, value);
            break;
        }
        case PARAM_ID_SOC: {
            // Range: 0 - 100.000000
            int32_t value = random(0, 100000000.0);
            _packInt32(dataPtr, value);
            break;
        }
        case PARAM_ID_TEMP: {
            // Range: -10.0 - 100.0
            int32_t value = random(-100, 1000);
            _packInt16(dataPtr + 1, value);
            dataPtr[3] = random(0,2);
            break;
        }
        default: {
            break;
        }
    }
}

void CanBehaviorTinyBms::_packFloat(uint8_t* dataPtr, float value) {
    memcpy((void*)dataPtr, (void*)&value, 4);
}

void CanBehaviorTinyBms::_packInt16(uint8_t* dataPtr, int16_t value) {
    dataPtr[0] = value;
    dataPtr[1] = value >> 8;
}

void CanBehaviorTinyBms::_packInt32(uint8_t* dataPtr, int32_t value) {
    dataPtr[0] = value;
    dataPtr[1] = value >> 8;
    dataPtr[2] = value >> 16;
    dataPtr[3] = value >> 24;
}