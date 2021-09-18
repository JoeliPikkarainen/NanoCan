#ifndef CAN_IF_H
#define CAN_IF_H

#include <Arduino.h>
#include <SPI.h>
#include "mcp_can.h"

class CAN_FRAME{

public:
    CAN_FRAME();

    unsigned long id;
    uint8_t bf[8];

private:

};

class CAN_IF{

public:
    CAN_IF();
    
    int init();
    MCP_CAN* getCan();

    bool receive(CAN_FRAME& frame);

private:
    MCP_CAN* m_can;

};
#endif