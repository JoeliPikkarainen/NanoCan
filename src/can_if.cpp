#include "can_if.h"

CAN_IF::CAN_IF() 
{
    
}

int CAN_IF::init() 
{
    m_can = new MCP_CAN(10);
    int ok = (m_can->begin(CAN_500KBPS) == CAN_OK) ? 0 : 1;
    return ok;
}

MCP_CAN* CAN_IF::getCan() 
{
    return m_can;
}

bool CAN_IF::receive(CAN_FRAME& frame) 
{
    if(m_can->checkReceive() != CAN_MSGAVAIL)
        return false;

    uint8_t len = 0;
    m_can->readMsgBuf(&len,frame.bf);
    frame.id = m_can->getCanId();

    return true;
}


