#ifndef _SIM_CAN_H_
#define _SIM_CAN_H_

#include "can.h"
#include "Sim.h"
#include "mcp2515_can.h"
#include "CanBehavior.h"

using namespace can;

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
        SimCan(CanBehavior** behaviors);

        void begin();

        void handle();

        void send(CanMessage msg, String serialMsg);

        String getHumanName();

        /**
         * Convert error code into descriptive error message
         * 
         * @param errorCode
         * @return error message
         **/ 
        static String getErrorDescription(uint8_t errorCode);

    private:
        mcp2515_can* _can;
        unsigned long long _last_transmit;
        CanBehavior** _behaviors;

        void _transmit();
        
        void _receive();

        /**
         * @brief Serial output message for when can messages are transmitted
         * 
         * @param msg the message being tranmsmitted
         * @param error the transmission error message from mcp2515_can
         */
        static void _serialSendMessage(const CanMessage& msg, uint8_t error, String serialMsg);

        /**
         * @brief Serial output message for when can messages are received
         * 
         * @param id id of received message
         * @param len length of received message
         * @param buf data from received message
         */
        static void _serialReceiveMessage(const CanMessage& msg);

        // SimCan delegate class sender
        class Sender : public Delegate {
            public:
                Sender(SimCan* owner) : _owner(owner) { }

                ~Sender() { }

                void send(CanMessage msg, String serialMsg);
            
            private:
                SimCan* _owner;
        };
};

#endif