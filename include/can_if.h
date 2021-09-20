#ifndef CAN_IF_H
#define CAN_IF_H

#include <Arduino.h>
#include <SPI.h>
#include "mcp_can.h"
#include <CAN.h>

class CAN_FRAME{

public:
    CAN_FRAME();

    unsigned long id;
    uint8_t bf[8];
    uint8_t len;

private:

};

class CAN_IF{

public:
    CAN_IF();
    
    bool init();
    bool init2();
    MCP2515Class getCan();
    MCP_CAN* getCan2();

    bool receive2(CAN_FRAME& frame);
    bool receive(CAN_FRAME& frame);

private:
    MCP_CAN* m_can;

};
#endif