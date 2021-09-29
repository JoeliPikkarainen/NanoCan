#include "can_if.h"

CAN_IF::CAN_IF() 
{
    
}

bool CAN_IF::init() 
{
    CAN.setPins(/*cc*/10, /*int*/9);
    if(!CAN.begin(rateKbs * 1E3)){
        return false;
    }
    else{
        inited = true;
        return true;
    }
}

MCP2515Class CAN_IF::getCan() 
{
    return CAN;
}

bool CAN_IF::receive(CAN_FRAME& frame) 
{
    if(!inited)
        return false;
        
    int packet_size = CAN.parsePacket();
    if(packet_size == 0){
        return false;
    }

    frame.received = true;

    if(CAN.packetRtr()){
        //return false;
    }

    frame.id = CAN.packetId();
    frame.len = packet_size;
    frame.bf = CAN.read();

    return true;
}

void CAN_IF::sleepEnable(bool enable) 
{
    if(enable){
        CAN.sleep();
    }
    else{
        CAN.wakeup();
    }
}



CAN_FRAME::CAN_FRAME() 
{
    
}
