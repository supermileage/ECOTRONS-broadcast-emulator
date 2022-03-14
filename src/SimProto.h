#pragma once

#include "Arduino.h"
#include "Sim.h"

#define ECU_BAUD_RATE           115200
#define ECU_PACKET_SIZE         27
#define ECU_UPDATE_MS           100

#define ECU_HEADER_1            0x80
#define ECU_HEADER_2            0x8F
#define ECU_HEADER_3            0xEA
#define ECU_DATA_FIELD_LENGTH   0x16
#define ECU_SERVICE_ID          0x50

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
        uint8_t _ecu_data[ECU_PACKET_SIZE];

        /**
         * Randomize data in ECU data fields
         **/
        void _randomizeData();

        /**
         * Calculate checksum based on all fields
         **/
        void _calculateChecksum();

};

