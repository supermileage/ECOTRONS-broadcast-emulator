#ifndef _SIM_CAN_H_
#define _SIM_CAN_H_

#include "Sim.h"
#include "mcp2515_can.h"

#define CAN_CS_PIN          10
#define CAN_UPDATE_MS       250
#define CAN_FRAME           0

#define CAN0_ID             0x00
#define CAN0_DATA_LENGTH    8
#define CAN1_ID             0xA2
#define CAN1_DATA_LENGTH    5

class SimCan : public Sim {
    public:

        SimCan();

        void begin();

        void handle();

        String getHumanName();

    private:
        mcp2515_can* _can; 
        unsigned char _can0_data[CAN0_DATA_LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7};
        unsigned char _can1_data[CAN1_DATA_LENGTH] = {4, 3, 2, 1, 0};
        unsigned long long _can_last_update;

};

#endif