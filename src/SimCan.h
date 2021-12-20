#ifndef _SIM_CAN_H_
#define _SIM_CAN_H_

#include "Sim.h"
#include "mcp2515_can.h"
#include "CanBehavior.h"

// This struct contains all the components of a CAN message. dataLength must be <= 8, 
// and the first [dataLength] positions of data[] must contain valid data
typedef uint8_t CanBuffer[8];
struct CanMessage {
    uint32_t id;
    uint8_t dataLength;
    CanBuffer data;
};

// Turn on/off serial debugging
#define DEBUG_SERIAL 1

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
        SimCan(CanBehavior* behavior);

        void begin();

        void handle();

        String getHumanName();

        /**
         * Convert error code into descriptive error message
         * 
         * @param errorCode
         * @return error message
         **/ 
        static String getErrorDescription(uint8_t errorCode);

        /**
         * @brief Serial output message for when can messages are transmitted
         * 
         * @param msg the message being tranmsmitted
         * @param error the transmission error message from mcp2515_can
         */
        static void serialTransmitMessage(CanMessage msg, uint8_t error);

        /**
         * @brief Serial output message for when can messages are received
         * 
         * @param id id of received message
         * @param len length of received message
         * @param buf data from received message
         */
        static void serialReceiveMessage(uint16_t id, uint8_t len, CanBuffer buf);

    private:
        mcp2515_can* _can;
        unsigned long long _last_transmit;
        CanBehavior* _behavior;
};

#endif