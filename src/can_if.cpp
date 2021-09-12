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


