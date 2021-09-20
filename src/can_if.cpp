#include "can_if.h"

CAN_IF::CAN_IF() 
{
    
}

bool CAN_IF::init() 
{
    //CAN.setPins(/*cc*/13, /*int*/12);
    //CAN.setSPIFrequency(14000);
    if(!CAN.begin(500E3)){
        return false;
    }
    else{
        return true;
    }
}

bool CAN_IF::init2() 
{
    m_can = new MCP_CAN(10);
    bool ok = (m_can->begin(CAN_500KBPS) == CAN_OK) ? true : false;
    return ok;
}

MCP2515Class CAN_IF::getCan() 
{
    return CAN;
}

MCP_CAN* CAN_IF::getCan2() 
{
    return m_can;
}

bool CAN_IF::receive2(CAN_FRAME& frame) 
{
    if(m_can->checkReceive() != CAN_MSGAVAIL)
        return false;

    uint8_t len = 0;
    m_can->readMsgBuf(&len,frame.bf);
    frame.id = m_can->getCanId();
    frame.len = len;

    return true;
}

bool CAN_IF::receive(CAN_FRAME& frame) 
{
    int packet_size = CAN.parsePacket();
    if(packet_size == 0){
        return false;
    }
    if(CAN.packetRtr()){
        return false;
    }

    frame.id = CAN.packetId();
    frame.len = packet_size;
    frame.bf[0] = CAN.read();

    return true;
}



CAN_FRAME::CAN_FRAME() 
{
    
}
