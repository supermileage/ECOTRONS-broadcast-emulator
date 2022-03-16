#pragma once

#include "Arduino.h"
#include "Sim.h"

#define ECU_PACKET_SIZE         27

// Simulator for Proto Engine Computer Unit (ECU)
class SimProto : public Sim {
    public:

        /**
         * CONSTRUCTOR
         * 
         * @param updateInterval is the interval at which to update sensor values (ms)
         * */
        SimProto(uint32_t updateInterval) : Sim(updateInterval) {}

        void begin() override;

        void handle();

    private:
        uint8_t _ecuData[ECU_PACKET_SIZE];

        /**
         * Randomize data in ECU data fields
         **/
        void _randomizeData();

        /**
         * Calculate checksum based on all fields
         **/
        void _calculateChecksum();

        void _packValue(uint8_t* dataPtr, int16_t value);
};

