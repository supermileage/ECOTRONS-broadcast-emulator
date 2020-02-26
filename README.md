# ECOTRONS Broadcast Simulator

This is a simple sketch for an Arduino (or any PlatformIO with Arduino framework-compatible MCU) to simulate an ECOTRONS ECU. It's tailored for V1.2 of the ECU; later versions have different packet lengths. 

The following packet is broadcast over RS232 at a rate of 115200, 8 data bits, no partiy, and 1 stop bit every 100ms.

| Position | Type | Description             |
| -------- | ---- | ----------------------- |
| 0        | byte | Header1: 0x80           |
| 1        | byte | Header2: 0x8F           |
| 2        | byte | Header3: 0xEA           |
| 3        | byte | Data field length: 0x16 |
| 4        | byte | Service ID: 0x50        |
| 5..25    | byte | Broadcast data          |
| 26       | byte | Checksum                |

The checksum is the sum of bytes 0-25.

The byte ordering is in big endian.