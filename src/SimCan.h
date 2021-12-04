#ifndef _SIM_CAN_H_
#define _SIM_CAN_H_

#include "Sim.h"
#include "mcp2515_can.h"

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
#define CAN_TRANSMIT_INTERVAL 1000

// Transmit Messages
const CanMessage TEST1 = {0x14, 8, {0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
const CanMessage TEST2 = {0x2D, 8, {0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00}};
const CanMessage TRANSMIT_MSGS[] = {TEST1, TEST2};

// BMS Settings
#define BMS_REQUEST_ID      0x201
#define BMS_RESPONSE_ID     0x241
#define BMS_REQUEST_LENGTH  8

const CanMessage BMS_RESPONSE[] =   {{BMS_RESPONSE_ID, 6, {0x14,0x01,0x00,0x00,0x40,0x42}}, // Pack Voltage         - 48.0
                                    {BMS_RESPONSE_ID, 6, {0x15,0x01,0xCD,0xCC,0x4C,0x3F}},  // Pack Current         - 0.8
                                    {BMS_RESPONSE_ID, 4, {0x16,0x01,0x04,0x10}},            // Max Cell Voltage     - 4100
                                    {BMS_RESPONSE_ID, 4, {0x17,0x01,0xD8,0x0E}},            // Min Cell Voltage     - 3800
                                    {BMS_RESPONSE_ID, 4, {0x18,0x01,0x93,0x00}},            // Current Status       - DISCHARGING
                                    {BMS_RESPONSE_ID, 6, {0x1A,0x01,0xC0,0x9E,0xE6,0x05}},  // State of Charge      - 99000000
                                    {BMS_RESPONSE_ID, 5, {0x1B,0x01,0xFA,0x00,0x00}},       // Internal Temperature - 250
                                    {BMS_RESPONSE_ID, 5, {0x1B,0x01,0x04,0x01,0x01}},       // Battery Temp #1      - 260
                                    {BMS_RESPONSE_ID, 5, {0x1B,0x01,0x18,0x01,0x02}}};      // Battery Temp #2      - 280

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

        /**
         * Transmit all CAN messages in TRANSMIT_MSGS array, emulating CAN Accessories
         **/
        void _transmit();

        /**
         * Print all new CAN messages over serial (if enabled). If a BMS request is received, 
         * respond to it.
         **/
        void _receive();

        /**
         * Respond to a BMS request with some mock (static) data, emulating the BMS
         * 
         * @param len length in bytes of received message
         * @param buf data buffer
         **/       
        void _processBmsRequest(uint8_t len, uint8_t buf[]);

        /**
         * Convert error code into descriptive error message
         * 
         * @param errorCode
         * @return error message
         **/ 
        String _getErrorDescription(uint8_t errorCode);

};

#endif