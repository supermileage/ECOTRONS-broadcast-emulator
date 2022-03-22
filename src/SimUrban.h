#pragma once

#include "can.h"
#include "Sim.h"
#include "mcp2515_can.h"
#include "CanBehavior.h"

#define MAX_BEHAVIORS 100

using namespace can;

// Simulator for Urban CAN network
class SimUrban : public Sim {

    public:

        /**
         * CONSTRUCTOR
         * 
         * @param updateInterval is the interval at which to update sensor values (ms)
         * */
        SimUrban(uint32_t updateInterval) : Sim(updateInterval) {}

        /**
         * Add a CAN Behavior by pointer
         * 
         * @param behavior
         **/
        void addBehavior(CanBehavior* behavior);

		void removeBehavior(CanBehavior* behavior);

        void begin();

        void handle();

        /**
         * Send a CAN message
         * 
         * @param msg
         * @param serialMsg text to print in console if DEBUG_MSG_SEND is enabled
         **/
        void send(CanMessage msg, String serialMsg = "");

        /**
         * Convert error code into descriptive error message
         * 
         * @param errorCode
         * @return error message
         **/ 
        static String getErrorDescription(uint8_t errorCode);

    private:
        mcp2515_can* _can;
        CanBehavior* _behaviors[MAX_BEHAVIORS] = {};

        /**
         * Let all CAN Behaviors know they can transmit a scheduled message
         **/
        void _transmit();
        
        /**
         * Receive all messages in CAN RX buffer
         **/
        void _receive();

        // SimUrban delegate class sender
        class Sender : public Delegate {
            public:
                Sender(SimUrban* owner) : _owner(owner) { }

                ~Sender() { }

                void send(CanMessage msg, String serialMsg);
            
            private:
                SimUrban* _owner;
        };
};

