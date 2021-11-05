#ifndef _SIM_CAN_H_
#define _SIM_CAN_H_

#include "Sim.h"
#include "mcp2515_can.h"

#define CAN_DEBUG_BAUD_RATE 115200
#define CAN_CS_PIN          A5
#define CAN_UPDATE_MS       1000
#define CAN_FRAME           0

#define CAN0_ID             0x14
#define CAN0_DATA_LENGTH    8
#define CAN1_ID             0x2D
#define CAN1_DATA_LENGTH    8

class SimCan : public Sim {
    public:

        /**
         * Constructor (Emulator Operation)
         **/
        SimCan();

        /**
         * Constructor (Debug Operation)
         * 
         * @param serial port for outputting debug data
         **/
        SimCan(Stream *serial);

        void begin();

        void handle();

        String getHumanName();

    private:
        mcp2515_can* _can; 
        Stream *_serial = NULL;
        unsigned char _can0_data[CAN0_DATA_LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7};
        unsigned char _can1_data[CAN1_DATA_LENGTH] = {4, 3, 2, 1, 0, 0xF, 0xE, 0xD};
        unsigned long long _can_last_update;

        String getErrorDescription(uint8_t errorCode);

};

#endif