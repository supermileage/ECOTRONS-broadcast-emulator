#include "CanBehaviorSteering.h"

#define CAN_ID_STEERING_THROTTLE    0x01
#define CAN_ID_STEERING_READY       0x02

#define MIN_THROTTLE                0x01
#define MAX_THROTTLE                0xFF
#define MIN_READY                   0x00
#define MAX_READY                   0x07

#define READY_TO_DRIVE              0x03

const CanMessage MSG_THROTTLE = {CAN_ID_STEERING_THROTTLE, 1, {0x00}};
const CanMessage MSG_READY = {CAN_ID_STEERING_READY, 1, {0x00}};

void CanBehaviorSteering::transmit() {

    uint8_t ready = random(MIN_READY, MAX_READY);
    CanMessage msg = MSG_READY;
    msg.data[0] = ready;
    _sender->send(msg, String("STEERING READY"));

    msg = MSG_THROTTLE;

    if(ready == READY_TO_DRIVE) {
        msg.data[0] = random(MIN_THROTTLE, MAX_THROTTLE);
    }
    
    _sender->send(msg, String("STEERING THROTTLE"));

}