#include <Arduino.h>

#define PACKET_SIZE 27
#define RATE 100

uint8_t HEADER_1 = 0x80;
uint8_t HEADER_2 = 0x8F;
uint8_t HEADER_3 = 0xEA;
uint8_t DATA_FIELD_LENGTH = 0x16;
uint8_t SERVICE_ID = 0x50;

uint8_t BROADCAST_DATA[PACKET_SIZE];

unsigned long long time_ms;

void randomizeData();

void setup() {
    // 115200 baud rate, 8 data bits, no parity, 1 stop bit per datasheet
    Serial.begin(115200, SERIAL_8N1);
    BROADCAST_DATA[0] = HEADER_1;
    BROADCAST_DATA[1] = HEADER_2;
    BROADCAST_DATA[2] = HEADER_3;
    BROADCAST_DATA[3] = DATA_FIELD_LENGTH;
    BROADCAST_DATA[4] = SERVICE_ID;

    time_ms = millis();
}

void loop() {
    if (millis() - time_ms >= RATE) {
        time_ms = millis();
        randomizeData();

        for (int i = 0; i < PACKET_SIZE; i++) {
            Serial.write(BROADCAST_DATA[i]);
        }
    }
}

void randomizeData() {
    uint8_t checksum = 0;
    for (int i = 5; i < PACKET_SIZE - 1; i++) {
        uint8_t value = random(0, 255);
        BROADCAST_DATA[i] = value;
        checksum += value;
    }
    BROADCAST_DATA[PACKET_SIZE - 1] = checksum;
}
