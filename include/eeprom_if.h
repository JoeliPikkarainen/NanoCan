#ifndef EEPROM_IF_H
#define EEPROM_IF_H

#include <math.h>
#include <stdint.h>

#define SECTOR_CAN_RATE 0x00
#define SECTOR_CAN_RATE_SIZE 0x02


class EEPROM_IF{

public:

    EEPROM_IF();

    void saveValue(const void* value, uint64_t sector, uint64_t sector_size);

    uint8_t loadu8(int sector);
    uint16_t loadu16(int sector);
    uint32_t loadu32(int sector);
    uint64_t loadu64(int sector);
    float loadf(int sector);

private:

};
#endif