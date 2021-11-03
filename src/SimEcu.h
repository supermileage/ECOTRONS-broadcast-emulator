#ifndef _SIM_ECU_H_
#define _SIM_ECU_H_

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

class SimEcu : public Sim {
    public:
        /**
         * Constructor 
         **/
        SimEcu(Stream &serial);

        void begin();

        void handle();

        String getHumanName();

    private:
        Stream* _serial;
        uint8_t _ecu_data[ECU_PACKET_SIZE];
        unsigned long long _ecu_last_update;

        /**
         * Randomize data in ECU data fields
         **/
        void _randomizeData();

};

#endif
