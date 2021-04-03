#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>

#define ECU_PACKET_SIZE         27
#define ECU_UPDATE_MS           5000
#define ECU_HEADER_1            0x80
#define ECU_HEADER_2            0x8F
#define ECU_HEADER_3            0xEA
#define ECU_DATA_FIELD_LENGTH   0x16
#define ECU_SERVICE_ID          0x50
#define ECU_LED_PIN             2

#define CAN_CS_PIN      10
#define CAN_UPDATE_MS   3000
#define CAN_ID          0x00
#define CAN_FRAME       0
#define CAN_DATA_LENGTH 8
#define CAN_LED_PIN     3

uint8_t ecu_data[ECU_PACKET_SIZE];
unsigned long long ecu_last_update;

MCP_CAN CAN0(CAN_CS_PIN); 
unsigned char can_data[8] = {0, 1, 2, 3, 4, 5, 6, 7};
unsigned long long can_last_update;

void setup() {
    // ECU: 115200 baud rate, 8 data bits, no parity, 1 stop bit per datasheet
    Serial.begin(115200, SERIAL_8N1);

    // ECU data
    ecu_data[0] = ECU_HEADER_1;
    ecu_data[1] = ECU_HEADER_2;
    ecu_data[2] = ECU_HEADER_3;
    ecu_data[3] = ECU_DATA_FIELD_LENGTH;
    ecu_data[4] = ECU_SERVICE_ID;

    // CAN begin
    SPI.begin();
    CAN0.begin(CAN_125KBPS,MCP_8MHz) == CAN_OK;

    ecu_last_update = millis();
    can_last_update = millis();
    pinMode(ECU_LED_PIN, OUTPUT);
    pinMode(CAN_LED_PIN, OUTPUT);
}

// Randomize data for ECU data
void randomizeData() {
    uint8_t checksum = 0;
    for (int i = 5; i < ECU_PACKET_SIZE - 1; i++) {
        uint8_t value = random(0, 255);
        ecu_data[i] = value;
        checksum += value;
    }
    ecu_data[ECU_PACKET_SIZE - 1] = checksum;
}

void loop() {
    // Check for and send ECU update
    if (millis() - ecu_last_update >= ECU_UPDATE_MS) {
        ecu_last_update = millis();
        randomizeData();

        for (int i = 0; i < ECU_PACKET_SIZE; i++) {
            Serial.write(ecu_data[i]);
        }

        digitalWrite(ECU_LED_PIN, HIGH);
    } else {
        digitalWrite(ECU_LED_PIN, LOW);
    }

    // Check for and send CAN update
    if (millis() - can_last_update >= CAN_UPDATE_MS) {
        can_last_update = millis();
        CAN0.sendMsgBuf(CAN_ID, CAN_FRAME, CAN_DATA_LENGTH, can_data);  

        digitalWrite(CAN_LED_PIN, HIGH);
    } else {
        digitalWrite(CAN_LED_PIN, LOW);
    }
}


