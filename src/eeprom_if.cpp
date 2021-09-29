#include "eeprom_if.h"

#include <avr/eeprom.h>

EEPROM_IF::EEPROM_IF()
{

}

void EEPROM_IF::saveValue(const void* value, uint64_t sector, uint64_t sector_size)
{
    eeprom_busy_wait();

    eeprom_write_block((const void*) value, (void*)sector, sector_size);
}

uint8_t EEPROM_IF::loadu8(int sector) 
{
    uint8_t retval;
    eeprom_read_block((void*)&retval,(const void*)sector,1);
    return retval;
}

uint16_t EEPROM_IF::loadu16(int sector) 
{
    uint16_t retval;
    eeprom_read_block((void*)&retval,(const void*)sector,2);
    return retval;
}

uint32_t EEPROM_IF::loadu32(int sector) 
{
    uint32_t retval;
    eeprom_read_block((void*)&retval,(const void*)sector,4);
    return retval;
}

uint64_t EEPROM_IF::loadu64(int sector) 
{
    uint64_t retval;
    eeprom_read_block((void*)&retval,(const void*)sector,8);
    return retval;
}

float EEPROM_IF::loadf(int sector) 
{
    float retval;
    eeprom_read_block((void*)&retval,(const void*)sector,4);
    return retval;
}