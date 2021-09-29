#ifndef CAN_IF_H
#define CAN_IF_H

#include <Arduino.h>
#include <SPI.h>
#include <CAN.h>

#include "com_frame.h"



class CAN_IF{

public:
    CAN_IF();
    
    bool init();
    bool isInited() { return inited;};

    MCP2515Class getCan();
    
    bool receive(CAN_FRAME& frame);
    void sleepEnable(bool enable);

    uint16_t rateKbs = 500;

private:
    bool inited = false;
};
#endif