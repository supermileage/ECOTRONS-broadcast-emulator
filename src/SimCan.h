#ifndef _SIM_CAN_H_
#define _SIM_CAN_H_

#include "Sim.h"
#include "mcp2515_can.h"

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
#define CAN_TRANSMIT_INTERVAL       200

// Transmit Messages
const CanMessage TEST1 = {0x14, 8, {0, 1, 2, 3, 4, 5, 6, 7}};
const CanMessage TEST2 = {0x2D, 8, {7, 6, 5, 4, 3, 2, 1, 0}};
const CanMessage TRANSMIT_MSGS[] = {TEST1, TEST2};

// BMS Settings
#define BMS_REQUEST_ID      0x201
#define BMS_RESPONSE_ID     0x241
#define NUM_BMS_PROPERTIES  9

const uint8_t BMS_PROPERTY[NUM_BMS_PROPERTIES] =   {0x14,   // pack voltage
                                                    0x15,   // pack current
                                                    0x16,   // max cell voltage
                                                    0x17,   // min cell voltage
                                                    0x18,   // current status
                                                    0x1A,   // state of charge
                                                    0x1B,   // Temperatures
                                                    0x1B,
                                                    0x1B};  

const uint8_t BMS_RESPONSE_LENGTH[NUM_BMS_PROPERTIES] =    {4,
                                                            4, 
                                                            2, 
                                                            2, 
                                                            2,
                                                            4,
                                                            3,
                                                            3, 
                                                            3};

const uint8_t BMS_RESPONSE_DATA[NUM_BMS_PROPERTIES][4] =   {{0x00,0x00,0x40,0x42},    // 48.0
                                                            {0xCD,0xCC,0x4C,0x3F},    // 0.8
                                                            {0x04,0x10,0x00,0x00},    // 4100
                                                            {0xD8,0x0E,0x00,0x00},    // 3800
                                                            {0x93,0x00,0x00,0x00},    // DISCHARGING
                                                            {0xC0,0x9E,0xE6,0x05},    // 99000000
                                                            {0xFA,0x00,0x00,0x00},    // 250 (Internal Temp)
                                                            {0x04,0x01,0x01,0x00},    // 260 (Battery Temp #1)
                                                            {0x18,0x01,0x02,0x00}};   // 280 (Battery Temp #2)



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
        unsigned long long _last_transmit;

        void _transmit();
        void _receive();
        void _processCanRequest(uint8_t len, uint8_t buf[]);

        String _getErrorDescription(uint8_t errorCode);

};

#endif