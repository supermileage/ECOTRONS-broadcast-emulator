#ifndef _SIM_CAN_H_
#define _SIM_CAN_H_

#include "Sim.h"
#include "mcp2515_can.h"
#include "CanBehavior.h"

// This struct contains all the components of a CAN message. dataLength must be <= 8, 
// and the first [dataLength] positions of data[] must contain valid data
struct CanMessage {
    uint32_t id;
    uint8_t dataLength;
    uint8_t data[8];
};

// CAN Settings
#define CAN_DEBUG_BAUD_RATE 115200
#define CAN_CS_PIN          A5
#define CAN_FRAME           0

// Transmit Settings
#define CAN_TRANSMIT_INTERVAL 500

class CanBehavior;

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
        SimCan(Stream *serial, CanBehavior* behavior);

        void begin();

        virtual void handle();

        virtual String getHumanName();

        /**
         * Convert error code into descriptive error message
         * 
         * @param errorCode
         * @return error message
         **/ 
        static String getErrorDescription(uint8_t errorCode);

    private:
        mcp2515_can* _can; 
        Stream *_serial = NULL;
        unsigned long long _last_transmit;
        CanBehavior* _behavior;
};

#endif