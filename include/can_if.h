#ifndef CAN_IF_H
#define CAN_IF_H

#include <Arduino.h>
#include <SPI.h>
#include "mcp_can.h"

class CAN_IF{

public:
    CAN_IF();
    
    int init();
    MCP_CAN* getCan();

private:
    MCP_CAN* m_can;

};
#endif